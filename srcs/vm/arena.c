/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 23:18:10 by toliver           #+#    #+#             */
/*   Updated: 2020/01/03 22:36:40 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_create_process(t_arena *arena, int owner, int pos)
{
	if (!(ft_add_process(arena, pos)))
		return (0);
	*((int32_t*)(&arena->process->reg[0].mem)) = (int32_t)owner;
	return (1);
}

void		ft_fill_arena(t_arena *arena, t_champ *champ, int pos)
{
	int		i;

	i = 0;
	while (i < (int)champ->header.prog_size)
	{
		arena->arena[pos + i].value = champ->content[i];
		arena->arena[pos + i].writer = champ->number;
		i++;
	}
}

int			ft_init_process(t_env *env, int space_between)
{
	t_champ	*ptr;
	int		actualpos;

	actualpos = 0;
	ptr = env->champs;
	while (ptr)
	{
		ft_fill_arena(&env->arena, ptr, actualpos);
		if (!(ft_create_process(&env->arena, ptr->number, actualpos)))
			return (0);
		actualpos += space_between;
		ptr = ptr->next;
	}
	return (1);
}

void		ft_set_arena(t_env *env, int champ_number)
{
	env->arena.cycles_to_die = CYCLE_TO_DIE;
	env->arena.actual_cycles_to_die = CYCLE_TO_DIE;
	env->arena.check_number = MAX_CHECKS;
	env->arena.last_live = -champ_number;
}

int			ft_init_arena(t_env *env)
{
	unsigned int	total_size;
	t_champ			*ptr;
	int				champ_number;
	int				space_between;

	ptr = env->champs;
	total_size = 0;
	champ_number = 0;
	env->arena.pid = 1;
	while (ptr)
	{
		total_size += ptr->header.prog_size;
		champ_number++;
		ptr = ptr->next;
	}
	if (total_size >= MEM_SIZE)
		return (ft_arena_error(NOT_ENOUGH_SPACE));
	if (champ_number == 0)
		return (ft_arena_error(NO_CHAMPIONS));
	space_between = MEM_SIZE / champ_number;
	ft_set_arena(env, champ_number);
	if (!ft_init_process(env, space_between))
		return (0);
	return (1);
}
