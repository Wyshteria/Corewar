/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jates- <jates-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:48:43 by toliver           #+#    #+#             */
/*   Updated: 2020/02/24 17:23:10 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_skip_spaces(t_env *env, t_file *file)
{
	int		size;
	int		i;
	char	buffer[51];
	int		retval;

	size = 0;
	while ((retval = read(file->fd, buffer, 50)) > 0)
	{
		buffer[retval] = '\0';
		i = 0;
		while (buffer[i] && (buffer[i] == ' ' || buffer[i] == '\t'))
		{
			file->col += 1;
			i++;
		}
		size += i;
		if (i != retval)
			break ;
	}
	if (retval == -1)
		ft_error(env, file, READ_ERROR);
	else if (retval == 0)
		file->mode = DONE;
	else
		ft_offset_head(env, file, size);
}

static int	read_file_fd(t_file *file, char *containing, char *buf)
{
	int		retval;
	int		size;
	int		i;

	size = 0;
	while ((retval = read(file->fd, buf, 50)) > 0)
	{
		i = 0;
		buf[retval] = '\0';
		while (buf[i] && ft_is_one_of(buf[i], containing))
			i++;
		size += i;
		if (i != retval)
			break ;
	}
	if (retval == -1)
		return (-1);
	if (retval == 0)
		file->mode = DONE;
	return (size);
}

int			ft_parse_while(t_file *file, char *containing, char **line)
{
	char	buf[51];
	int		size;
	int		retval;

	if ((size = read_file_fd(file, containing, buf)) == -1)
		return (ft_error(ft_get_env(), file, READ_ERROR));
	*line = (char*)ft_safe_malloc(sizeof(char) * (size + 1));
	ft_offset_head(ft_get_env(), file, 0);
	retval = read(file->fd, *line, size);
	if (retval == -1)
	{
		free(*line);
		*line = NULL;
		return (ft_error(ft_get_env(), file, READ_ERROR));
	}
	(*line)[retval] = '\0';
	ft_offset_head(ft_get_env(), file, size);
	ft_offset_lines(ft_get_env(), file, *line);
	return (1);
}

static int	read_until(t_file *file, char *limit, char *end, char *buf)
{
	int		retval;
	int		size;
	int		i;

	size = 0;
	while ((retval = read(file->fd, buf, 50)) > 0)
	{
		i = 0;
		buf[retval] = '\0';
		while (buf[i] && !(*end = ft_is_one_of(buf[i], limit)))
			i++;
		size += i;
		if (i != retval)
			break ;
	}
	if (retval == -1)
		return (-1);
	if (retval == 0)
		file->mode = DONE;
	return (size);
}

int			ft_parse_until(t_file *file, char *limit, char **line, int skipping)
{
	char	buf[51];
	int		size;
	int		retval;
	char	end;

	if ((size = read_until(file, limit, &end, buf)) == -1)
		return (ft_error(ft_get_env(), file, READ_ERROR));
	*line = (char*)ft_safe_malloc(sizeof(char) * (size + 1));
	ft_offset_head(ft_get_env(), file, 0);
	retval = read(file->fd, *line, size);
	if (retval == -1)
	{
		free(*line);
		*line = NULL;
		return (ft_error(ft_get_env(), file, READ_ERROR));
	}
	(*line)[retval] = '\0';
	ft_offset_head(ft_get_env(), file, size + (skipping ? 1 : 0));
	ft_offset_lines(ft_get_env(), file, *line);
	if (end && skipping)
		ft_offset_lines(ft_get_env(), file, ((char[]){end, '\0'}));
	return (1);
}
