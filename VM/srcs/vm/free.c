/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 06:27:16 by toliver           #+#    #+#             */
/*   Updated: 2019/12/06 06:30:07 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_free_env(t_env *env)
{
	ft_free_champs(env);
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
		ptr = tmp;;
	}
	env->champs = NULL;
}
