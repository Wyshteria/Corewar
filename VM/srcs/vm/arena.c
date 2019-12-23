/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 23:18:10 by toliver           #+#    #+#             */
/*   Updated: 2019/12/23 17:07:56 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_arena_error(int error)
{
	ft_dprintf(2, "%s: ", ft_get_env()->prog_name);
	if (error == NOT_ENOUGH_SPACE)
		ft_dprintf(2, "Not enough space in arena to place all champions\n");
	else if (error == NO_CHAMPIONS)
		ft_dprintf(2, "No champion or no working champion were given\n");
	else if (error == MALLOC_FAIL)
		ft_dprintf(2, "malloc failed : %s\n", strerror(errno));
	return (0);
}

void			ft_dump_arena(t_arena *arena)
{
	int			i;
	t_process	*ptr;
	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%.2x(%d) ", arena->arena[i].value, arena->arena[i].writer);
		i++;
	}
	ft_printf("\n");
	ptr = arena->process;
	while (ptr)
	{
		ft_printf("process:\n");
		ft_printf("\tpos = %d\n", ptr->pos);
		ft_printf("\topcode_value = %hhu\n", ptr->opcode_value);
		ft_printf("\tcycles to exec = %d\n", ptr->cycles_to_exec);
		ft_printf("\top size = %d\n", ptr->op_size);
		ft_printf("\tpid = %d\n", ptr->pid);
		ptr = ptr->next;
	}
}

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
	int				actualpos;

	actualpos = 0;
	ptr = env->champs;
	while (ptr)
	{
		ft_fill_arena(&env->arena, ptr, actualpos);
		if (!(ft_create_process(&env->arena, ptr->number ,actualpos)))
			return (0);
		actualpos += space_between;
		ptr = ptr->next;
	}
	return (1);
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
	ptr = env->champs;
	env->arena.cycles_to_die = CYCLE_TO_DIE;
	env->arena.actual_cycles_to_die = CYCLE_TO_DIE;
	env->arena.check_number = MAX_CHECKS;
	if (!ft_init_process(env, space_between))
		return (0);
	return (1);
}
