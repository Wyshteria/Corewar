/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 04:59:05 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 05:01:01 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_increment_cycles(t_env *env)
{
	t_arena		*arena;

	arena = &(env->arena);
	arena->cycles++;
	arena->actual_cycles_to_die--;
	if (ft_verbose_flag(VERBOSE_CYCLES_FLAG))
		ft_verbose_cycles(env);
}

int			ft_get_real_size(int type, int dir_two_bytes)
{
	if (type == T_REG)
		return (1);
	else if (type == T_IND || (type == T_DIR && dir_two_bytes))
		return (2);
	else if (type == T_DIR && !dir_two_bytes)
		return (4);
	return (0);
}

void		ft_parse_op_params(t_opcode *op, t_process *process, t_arena *arena)
{
	int		i;
	int		param_size;

	i = 0;
	while (i < op->params_number)
	{
		param_size = ft_get_real_size(op->params_types[i], op->dir_two_bytes);
		op->params[i] = ft_parse_value(arena,
				(process->pos + op->size) % MEM_SIZE, param_size);
		op->size += param_size;
		i++;
	}
}

void		ft_set_op_params_types(t_opcode *op)
{
	int		i;

	if (!op->need_encoding_byte)
		op->params_types[0] = g_op_tab[op->opcode].params[0];
	else
	{
		op->params_types[0] = ((op->encoding_byte & 0b11000000) >> 6);
		op->params_types[1] = ((op->encoding_byte & 0b110000) >> 4);
		op->params_types[2] = ((op->encoding_byte & 0b1100) >> 2);
		op->params_types[3] = (op->encoding_byte & 0b11);
		i = 0;
		while (i < g_op_tab[op->opcode].params_number)
		{
			if (op->params_types[i] == 3)
				op->params_types[i] = T_IND;
			if (!(op->params_types[i] & g_op_tab[op->opcode].params[i]))
				op->is_valid = 0;
			i++;
		}
	}
}

void		ft_exec_op(t_opcode *op, t_process *process, t_arena *arena)
{
	if (g_op_func[op->opcode] == NULL)
		ft_printf("(ne devrait pas arriver sauf sur 0)");
	else
	{
		if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG) && op->opcode != AFF)
			ft_verbose_op(arena, process, op);
		g_op_func[op->opcode](op, process, arena);
	}
}
