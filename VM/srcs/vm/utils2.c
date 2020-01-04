/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:38:09 by toliver           #+#    #+#             */
/*   Updated: 2020/01/03 22:38:32 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_write_in_arena(t_arena *arena, int pos, int32_t value, int owner)
{
	union u_converter	converter;
	int					i;

	converter.real_value = ft_swap(value);
	i = 0;
	if (pos < 0)
		pos = MEM_SIZE + pos;
	while (i < 4)
	{
		arena->arena[(pos + i) % MEM_SIZE].value = converter.value[i];
		arena->arena[(pos + i) % MEM_SIZE].writer = owner;
		i++;
	}
}

int32_t		ft_parse_value(t_arena *arena, int pos, int size)
{
	union u_converter	value;
	int					i;

	i = 0;
	value.value[0] = 0;
	value.value[1] = 0;
	value.value[2] = 0;
	value.value[3] = 0;
	if (pos < 0)
		pos = MEM_SIZE + pos;
	while (i < size)
	{
		value.value[i] = arena->arena[((pos + i) % MEM_SIZE)].value;
		i++;
	}
	if (size == 4)
		value.real_value = ft_swap(value.real_value);
	else if (size == 2)
	{
		i = value.value[0];
		value.value[0] = value.value[1];
		value.value[1] = i;
	}
	return (value.real_value);
}

int32_t		ft_get_value_from_address(t_arena *arena, int pos, int32_t offset)
{
	int					realpos;
	int32_t				value;

	realpos = (pos + offset) % MEM_SIZE;
	if (realpos < 0)
		realpos = MEM_SIZE + realpos;
	value = ft_parse_value(arena, realpos, REG_SIZE);
	return (value);
}

int32_t		ft_get_value_from(t_opcode *op, t_process *process, t_arena *arena,
		int num)
{
	int32_t	value;

	if (op->params_types[num] == T_REG)
		value = *(int32_t*)process->reg[op->params[num] - 1].mem;
	else if (op->params_types[num] == T_DIR)
		value = op->params[num];
	else if (op->opcode == LLD || op->opcode == LLDI)
		value = ft_get_value_from_address(arena, process->pos, op->params[num]);
	else
		value = ft_get_value_from_address(arena, process->pos,
				((int32_t)((int16_t)op->params[num])) % IDX_MOD);
	return (value);
}

uint32_t	ft_swap(uint32_t toswap)
{
	uint32_t	swapped;

	swapped = ((toswap >> 24) & 0xff) |
		((toswap << 8) & 0xff0000) |
		((toswap >> 8) & 0xff00) |
		((toswap << 24) & 0xff000000);
	return (swapped);
}
