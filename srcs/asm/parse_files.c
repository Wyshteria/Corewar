/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboukrou <lboukrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 03:11:51 by lboukrou          #+#    #+#             */
/*   Updated: 2020/01/05 03:47:40 by lboukrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_parse_files_2(t_env *env, t_file **ptr)
{
	t_file	*tmp;

	if (!(ft_open_file(env, *ptr)))
	{
		tmp = *ptr;
		*ptr = (*ptr)->next;
		ft_delete_file(env, tmp);
		return (1);
	}
	else if (!(ft_parse_file(env, *ptr)))
	{
		close((*ptr)->fd);
		tmp = *ptr;
		*ptr = (*ptr)->next;
		ft_delete_file(env, tmp);
		return (1);
	}
	else
		return (0);
	return (1);
}

void		ft_parse_files(t_env *env)
{
	t_file	*ptr;
	t_file	*tmp;

	ptr = env->files;
	while (ptr)
	{
		if (ft_parse_files_2(env, &ptr))
			continue ;
		else if (!(ft_write_file(env, ptr)))
		{
			close(ptr->fd);
			tmp = ptr;
			ptr = ptr->next;
			ft_delete_file(env, tmp);
			continue;
		}
		close(ptr->fd);
		tmp = ptr;
		ptr = ptr->next;
		ft_delete_file(env, tmp);
	}
}

int			ft_parse_file(t_env *env, t_file *file)
{
	while (file->mode != DONE && file->mode != CRASH
			&& file->mode != CONTAIN_ERRORS)
	{
		ft_skip_spaces(env, file);
		ft_parse_token(env, file);
	}
	return (file->mode != CRASH && file->mode != CONTAIN_ERRORS);
}
