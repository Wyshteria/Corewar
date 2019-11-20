/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 22:24:50 by toliver           #+#    #+#             */
/*   Updated: 2019/08/10 21:31:51 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

static int			str_split(char **str, char **line)
{
	char			*tmp;
	char			*newline;

	newline = ft_strchr(*str, '\n');
	if (newline == NULL)
	{
		*line = *str;
		*str = NULL;
		return (1);
	}
	if (!(*line = ft_strsub(*str, 0, newline == NULL ? 0 : newline - *str))
			|| !(tmp = ft_strdup(newline + 1)))
	{
		free(*line);
		free(*str);
		return (-1);
	}
	free(*str);
	*str = tmp;
	return (1);
}

static int			str_fill(char **str, const int fd)
{
	char			buf[BUFF_SIZE + 1];
	int				retval;
	char			*tmp;

	if (ft_strchr(*str, '\n'))
		return (1);
	while ((retval = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[retval] = '\0';
		if (!(tmp = ft_strjoin(*str, buf)) && retval != 0)
		{
			free(*str);
			return (-1);
		}
		free(*str);
		*str = tmp;
		if (ft_strchr(*str, '\n') || retval == 0)
			break ;
	}
	if (retval == 0)
	{
		free(*str);
		*str = NULL;
	}
	return (1);
}

int					ft_gnl(const int fd, char **line)
{
	static char		*str = NULL;

	*line = NULL;
	if (fd < 0 || str_fill(&str, fd) == -1)
		return (-1);
	if (str == NULL)
		return (0);
	return (str_split(&str, line));
}
