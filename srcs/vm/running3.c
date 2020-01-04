/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 05:01:34 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 05:02:27 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_run_once(t_env *env)
{
	ft_increment_cycles(env);
	ft_routine(env);
	if (env->arena.actual_cycles_to_die <= 0)
		ft_check_cycles(env);
	if (env->arena.process == NULL)
		ft_check_for_winner(env);
}

int			ft_check_champs(t_env *env)
{
	t_champ	*ptr;
	int		nbr;

	nbr = 0;
	ptr = env->champs;
	while (ptr)
	{
		nbr++;
		ptr = ptr->next;
	}
	if (nbr == 0)
	{
		ft_dprintf(2, "No working champions were given !\n");
		return (0);
	}
	if (nbr > 4)
	{
		ft_dprintf(2, "Too many champions were given %d (max 4)\n", nbr);
		return (0);
	}
	return (1);
}
