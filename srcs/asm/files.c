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

void		ft_free_file(t_file *file)
{
	(void)file;
}

void		ft_free_files(t_env *env)
{
	t_file	*ptr;
	t_file	*tmp;

	ptr = env->files;
	while (ptr)
	{
		tmp = ptr->next;
		ft_free_file(ptr);
		free(ptr);
		ptr = tmp;
	}
	env->files = NULL;
}
