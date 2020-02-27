/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 05:04:05 by toliver           #+#    #+#             */
/*   Updated: 2020/02/27 03:00:50 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_ld(t_opcode *op, t_process *process, t_arena *arena)
{
	int32_t	value;

	if (op->params_types[0] == T_DIR)
		value = ft_parse_value(arena, process->pos + 2, 4);
	else
		value = ft_parse_value(arena, process->pos +
				(int32_t)((int16_t)op->params[0]), 4);
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

void		ft_st(t_opcode *op, t_process *process, t_arena *arena)
{
	int32_t	value;
	int32_t pos;

	value = ft_get_value_from(op, process, arena, 0);
	op->params_parsed[0] = op->params[0];
	op->params_parsed[1] = op->params[1];
	if (op->params_types[1] == T_REG)
		*(int32_t*)process->reg[op->params[1] - 1].mem = value;
	else
	{
		pos = ((op->params[1] % IDX_MOD) + process->pos) % MEM_SIZE;
		ft_write_in_arena(arena, pos, value, arena->arena[process->pos].writer);
	}
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
	{
		ft_verbose_params(op, process, 0b1000);
	}
	ft_move_process(op, process, arena);
}

void		ft_add(t_opcode *op, t_process *process, t_arena *arena)
{
	int32_t		value1;
	int32_t		value2;
	int32_t		result;

	value1 = ft_get_value_from(op, process, arena, 0);
	value2 = ft_get_value_from(op, process, arena, 1);
	result = value1 + value2;
	op->params_parsed[0] = op->params[0];
	op->params_parsed[1] = op->params[1];
	op->params_parsed[2] = op->params[2];
	process->carry = (result == 0 ? 1 : 0);
	*(int32_t*)process->reg[op->params[2] - 1].mem = result;
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
	{
		ft_verbose_params(op, process, 0b1110);
	}
	ft_move_process(op, process, arena);
}

void		ft_sub(t_opcode *op, t_process *process, t_arena *arena)
{
	int32_t		value1;
	int32_t		value2;
	int32_t		result;

	value1 = ft_get_value_from(op, process, arena, 0);
	value2 = ft_get_value_from(op, process, arena, 1);
	result = value1 - value2;
	op->params_parsed[0] = op->params[0];
	op->params_parsed[1] = op->params[1];
	op->params_parsed[2] = op->params[2];
	process->carry = (result == 0 ? 1 : 0);
	*(int32_t*)process->reg[op->params[2] - 1].mem = result;
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
	{
		ft_verbose_params(op, process, 0b1110);
	}
	ft_move_process(op, process, arena);
}

void		ft_and(t_opcode *op, t_process *process, t_arena *arena)
{
	int32_t	value1;
	int32_t	value2;
	int32_t	result;

	value1 = ft_get_value_from(op, process, arena, 0);
	value2 = ft_get_value_from(op, process, arena, 1);
	result = (value1 & value2);
	process->carry = (result == 0 ? 1 : 0);
	op->params_parsed[0] = value1;
	op->params_parsed[1] = value2;
	op->params_parsed[2] = op->params[2];
	*(int32_t*)process->reg[op->params[2] - 1].mem = result;
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
	{
		ft_verbose_params(op, process, 0b0010);
	}
	ft_move_process(op, process, arena);
}
