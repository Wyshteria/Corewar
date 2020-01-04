/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 06:27:16 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 23:50:41 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_free_arena(t_env *env)
{
	t_process	*ptr;
	t_process	*tmp;

	ptr = env->arena.process;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
}

void		ft_free_env(t_env *env)
{
	ft_free_champs(env);
	ft_free_arena(env);
}

void		ft_free_champ(t_champ *champ)
{
	free(champ->content);
	free(champ);
}

void		ft_free_champs(t_env *env)
{
	t_champ	*ptr;
	t_champ	*tmp;

	ptr = env->champs;
	while (ptr)
	{
		tmp = ptr->next;
		ft_free_champ(ptr);
		ptr = tmp;
	}
	env->champs = NULL;
}

void		ft_free_process(t_process *process)
{
	free(process);
}
