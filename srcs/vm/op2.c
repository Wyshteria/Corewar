/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 05:04:48 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 05:05:01 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_or(t_opcode *op, t_process *process, t_arena *arena)
{
	int32_t	value1;
	int32_t	value2;
	int32_t	result;

	value1 = ft_get_value_from(op, process, arena, 0);
	value2 = ft_get_value_from(op, process, arena, 1);
	result = (value1 | value2);
	process->carry = (result == 0 ? 1 : 0);
	*(int32_t*)process->reg[op->params[2] - 1].mem = result;
	op->params_parsed[0] = value1;
	op->params_parsed[1] = value2;
	op->params_parsed[2] = op->params[2];
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
	{
		ft_verbose_params(op, process, 0b0010);
	}
	ft_move_process(op, process, arena);
}

void		ft_xor(t_opcode *op, t_process *process, t_arena *arena)
{
	int32_t	value1;
	int32_t	value2;
	int32_t	result;

	value1 = ft_get_value_from(op, process, arena, 0);
	value2 = ft_get_value_from(op, process, arena, 1);
	result = (value1 ^ value2);
	process->carry = (result == 0 ? 1 : 0);
	*(int32_t*)process->reg[op->params[2] - 1].mem = result;
	op->params_parsed[0] = value1;
	op->params_parsed[1] = value2;
	op->params_parsed[2] = op->params[2];
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
	{
		ft_verbose_params(op, process, 0b0010);
	}
	ft_move_process(op, process, arena);
}

void		ft_zjmp(t_opcode *op, t_process *process, t_arena *arena)
{
	op->params_parsed[0] = (int32_t)((int16_t)op->params[0]);
	op->flag = process->carry;
	if (process->carry == 1)
	{
		process->pos = (process->pos + (op->params[0] % IDX_MOD)) % MEM_SIZE;
		if (process->pos < 0)
			process->pos = MEM_SIZE + process->pos;
		process->need_refresh = 1;
	}
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
	{
		ft_verbose_params(op, process, 0);
	}
	if (process->carry == 0)
		ft_move_process(op, process, arena);
}

void		ft_ldi(t_opcode *op, t_process *process, t_arena *arena)
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
	offset = (((value1 + value2) % IDX_MOD) + process->pos) % MEM_SIZE;
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

void		ft_sti(t_opcode *op, t_process *process, t_arena *arena)
{
	int32_t	param1;
	int32_t	param2;
	int32_t	result;

	result = 0;
	param1 = ft_get_value_from(op, process, arena, 1);
	param2 = ft_get_value_from(op, process, arena, 2);
	result = param1 + param2;
	result = (result % IDX_MOD + process->pos) % MEM_SIZE;
	result = (result < 0 ? MEM_SIZE + result : result);
	ft_write_in_arena(arena, result,
			*(int32_t*)process->reg[op->params[0] - 1].mem,
			arena->arena[process->pos].writer);
	op->params_parsed[0] = op->params[0];
	op->params_parsed[1] = param1;
	op->params_parsed[2] = param2;
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
	{
		ft_verbose_params(op, process, 0b1000);
	}
	ft_move_process(op, process, arena);
}
