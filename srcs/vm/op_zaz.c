/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zaz.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:55:13 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 01:14:47 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_live(t_opcode *op, t_process *process, t_arena *arena)
{
	int32_t	value;
	t_champ	*champ;

	value = ft_parse_value(arena, (process->pos + 1) % MEM_SIZE, 4);
	op->params_parsed[0] = value;
	if (ft_verbose_flag(VERBOSE_LIVES_FLAG))
	{
		ft_verbose_params(op, process, 0);
	}
	if ((champ = ft_get_champ(value)))
	{
		if (ft_verbose_flag(VERBOSE_LIVES_FLAG))
			ft_printf("Player %d (%s) is said to be alive\n",
					-champ->number, champ->header.prog_name);
		arena->last_live = value;
	}
	process->live_number += 1;
	process->last_live = arena->cycles;
	ft_move_process(op, process, arena);
}

/*
** THIS FUNCTION IS INCORRECT
** however, I tried to copy the behavior of the Zaz vm, so it only reads 2 bytes
** instead of 4
*/

void		ft_lld(t_opcode *op, t_process *process, t_arena *arena)
{
	int		reg_number;
	int32_t	value;

	reg_number = op->params[1];
	if (op->params_types[0] == T_DIR)
		value = ft_parse_value(arena, process->pos + 2, 4);
	else
		value = ft_parse_value(arena, process->pos + op->params[0], 2);
	op->params_parsed[0] = value;
	op->params_parsed[1] = op->params[1];
	*((uint32_t*)(process->reg[op->params[1] - 1].mem)) = value;
	if (value == 0)
		process->carry = 1;
	else
		process->carry = 0;
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
	{
		ft_verbose_params(op, process, 0b0100);
	}
	ft_move_process(op, process, arena);
}

void		ft_check_for_winner(t_env *env)
{
	t_champ	*highest;

	highest = ft_get_champ(env->arena.last_live);
	if (!(env->flags & NCURSES_FLAG))
		ft_printf("Contestant %d, \"%s\", has won !\n", -highest->number,
				highest->header.prog_name);
}
