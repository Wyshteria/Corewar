/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboukrou <lboukrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 22:19:36 by lboukrou          #+#    #+#             */
/*   Updated: 2020/01/04 22:23:17 by lboukrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_offset_head(t_env *env, t_file *file, size_t size)
{
	file->offset = lseek(file->fd, file->offset + size, SEEK_SET);
	if (file->offset == -1)
	{
		ft_error(env, file, LSEEK_ERROR);
		return (0);
	}
	return (1);
}

int			ft_offset_lines(t_env *env, t_file *file, char *str)
{
	int		i;

	i = 0;
	(void)env;
	while (str && str[i])
	{
		if (str[i] == NEWLINE_CHAR)
		{
			file->line += 1;
			file->col = 1;
		}
		else
			file->col += 1;
		i++;
	}
	return (1);
}
