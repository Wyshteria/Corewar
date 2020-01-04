/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 05:05:05 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 05:05:28 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_fork(t_opcode *op, t_process *process, t_arena *arena)
{
	int32_t	pos;

	pos = ((int16_t)op->params[0]) % IDX_MOD;
	ft_clone_process(arena, process, pos);
	op->params_parsed[0] = ((int16_t)op->params[0]);
	op->params_parsed[1] = op->params_parsed[0] % IDX_MOD;
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
	{
		ft_verbose_params(op, process, 0);
	}
	ft_move_process(op, process, arena);
}

void		ft_lldi(t_opcode *op, t_process *process, t_arena *arena)
{
	int32_t	value1;
	int32_t	value2;
	int32_t	value3;
	int32_t	offset;

	value1 = ft_get_value_from(op, process, arena, 0);
	value2 = ft_get_value_from(op, process, arena, 1);
	op->params_parsed[0] = value1;
	op->params_parsed[1] = value2;
	op->params_parsed[2] = op->params[2];
	offset = (((value1 + value2)) + process->pos) % MEM_SIZE;
	if (offset < 0)
		offset = MEM_SIZE + offset;
	value3 = ft_parse_value(arena, offset, 4);
	*(int32_t*)process->reg[op->params[2] - 1].mem = value3;
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
	{
		ft_verbose_params(op, process, 0b0010);
	}
	ft_move_process(op, process, arena);
}

void		ft_lfork(t_opcode *op, t_process *process, t_arena *arena)
{
	ft_clone_process(arena, process, op->params[0]);
	op->params_parsed[0] = op->params[0];
	op->params_parsed[1] = op->params[0];
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
	{
		ft_verbose_params(op, process, 0);
	}
	ft_move_process(op, process, arena);
}

void		ft_aff(t_opcode *op, t_process *process, t_arena *arena)
{
	char	value;

	value = ft_get_value_from(op, process, arena, 0);
	if (ft_get_env()->flags & AFF_FLAG)
		ft_printf("Aff: %c\n", value);
	ft_move_process(op, process, arena);
}
