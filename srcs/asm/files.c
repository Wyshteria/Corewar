/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 21:18:05 by toliver           #+#    #+#             */
/*   Updated: 2019/11/25 22:43:58 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_free_label(t_file *file)
{
	t_label	*ptr;
	t_label	*tmp;

	ptr = file->label;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
}

void		ft_free_file(t_file *file)
{
	t_token	*ptr;
	t_token *tmp;

	ptr = file->tokens;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr->value);
		free(ptr);
		ptr = tmp;
	}
	file->tokens = NULL;
}

void		ft_free_files(t_env *env)
{
	t_file	*ptr;
	t_file	*tmp;

	ptr = env->files;
	while (ptr)
	{
		tmp = ptr->next;
		ft_free_label(ptr);
		ft_free_file(ptr);
		free(ptr);
		ptr = tmp;
	}
	env->files = NULL;
}
