/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 04:54:17 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 04:58:14 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_check_op_valid(t_opcode *op)
{
	int		i;

	if (!op->is_valid)
		return ;
	i = 0;
	while (i < g_op_tab[op->opcode].params_number)
	{
		if ((op->params_types[i] == T_IND ||
				(op->params_types[i] == T_DIR && op->dir_two_bytes))
				&& op->params[i] & 0x8000)
			op->params[i] = (int32_t)((int16_t)op->params[i]);
		if (op->params_types[i] == T_REG &&
				(op->params[i] > REG_NUMBER || op->params[i] == 0))
			op->is_valid = 0;
		i++;
	}
}

void		ft_parse_op(t_opcode *op, t_arena *arena, t_process *process)
{
	op->size = 1;
	if ((op->opcode = process->opcode_value) >= 17 || op->opcode <= 0)
	{
		op->is_valid = 0;
		return ;
	}
	op->is_valid = 1;
	op->opcode_name = g_op_tab[op->opcode].opcode;
	op->params_number = g_op_tab[op->opcode].params_number;
	op->dir_two_bytes = g_op_tab[op->opcode].t_dir_is_two_bytes;
	if ((op->need_encoding_byte = g_op_tab[op->opcode].need_encoding_byte) == 1)
	{
		op->encoding_byte = arena->arena[((process->pos + 1) % MEM_SIZE)].value;
		op->size += 1;
	}
	ft_set_op_params_types(op);
	ft_parse_op_params(op, process, arena);
	ft_check_op_valid(op);
}

void		ft_try_op(t_env *env, t_process *process)
{
	t_opcode	opcode;

	ft_bzero(&opcode, sizeof(t_opcode));
	ft_parse_op(&opcode, &env->arena, process);
	if (opcode.is_valid)
		ft_exec_op(&opcode, process, &env->arena);
	else
		ft_move_process(&opcode, process, &env->arena);
}

void		ft_kill_process(t_arena *arena, t_process *process)
{
	t_process	*tmp;

	if (arena->process == process)
		arena->process = process->next;
	else
	{
		tmp = arena->process;
		while (tmp && tmp->next != process)
			tmp = tmp->next;
		tmp->next = process->next;
	}
	ft_free_process(process);
}

void		ft_decrease_cycle_to_die(t_arena *arena)
{
	arena->cycles_to_die -= CYCLE_DELTA;
	if (ft_verbose_flag(VERBOSE_CYCLES_FLAG))
		ft_printf("Cycle to die is now %d\n", arena->cycles_to_die);
}
