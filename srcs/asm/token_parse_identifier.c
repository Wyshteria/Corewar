/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse_identifier.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboukrou <lboukrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 21:33:41 by lboukrou          #+#    #+#             */
/*   Updated: 2020/01/05 02:01:54 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_is_label(t_file *file)
{
	char	buf[1];
	int		retval;

	retval = read(file->fd, buf, 1);
	if (retval == -1)
		ft_error(ft_get_env(), file, READ_ERROR);
	else if (buf[0] == LABEL_CHAR)
	{
		ft_offset_head(ft_get_env(), file, 1);
		return (1);
	}
	else
		ft_offset_head(ft_get_env(), file, 0);
	return (0);
}

int			ft_is_reg(char *str)
{
	int		i;

	if (str[0] == 'r')
	{
		i = 1;
		while (str[i])
		{
			if (str[i] < '0' || str[i] > '9')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
