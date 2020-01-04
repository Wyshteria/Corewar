/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:40:05 by toliver           #+#    #+#             */
/*   Updated: 2020/01/03 22:40:24 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_dump_process(t_process *process)
{
	int		i;

	i = 0;
	ft_printf("== DUMPING PROCESS %d ==\n", process->pid);
	ft_printf("actual_pos = %d\n", process->pos);
	ft_printf("dumping process register :\n");
	ft_printf("process lived : %d\n", process->live_number);
	while (i < REG_NUMBER)
	{
		ft_printf("\tregister %d = %d\n", i,
				*((int32_t*)(process->reg[i].mem)));
		i++;
	}
}

void		ft_dump_all_process(t_arena *arena)
{
	t_process	*process;

	process = arena->process;
	while (process)
	{
		ft_dump_process(process);
		process = process->next;
	}
}

void		ft_dump_op(t_opcode *op)
{
	ft_printf("==============================================\n");
	ft_printf("op opcode : %.2x | op name %s | op param number %d\n",
			op->opcode, op->opcode_name, op->params_number);
	ft_printf("op need an encoding byte : %s",
			op->need_encoding_byte ? "yes" : "no\n");
	if (op->need_encoding_byte)
		ft_printf(" | encoding byte : %hhb\n", op->encoding_byte);
	ft_printf("params types: %d %d %d %d\n", op->params_types[0],
			op->params_types[1], op->params_types[2], op->params_types[3]);
	ft_printf("params : %d %d %d %d\n", op->params[0], op->params[1],
			op->params[2], op->params[3]);
	ft_printf("is a valid operation ? %s | ", op->is_valid ? "yes" : "no");
	ft_printf("its size is : %d\n", op->size);
	ft_printf("==============================================\n");
}

void		ft_dump_verbose_flags(t_env *env)
{
	if (env->verbose_level == 0)
		ft_printf(" only essentials\n");
	else
	{
		ft_printf(":\n");
		if (env->verbose_level & VERBOSE_LIVES_FLAG)
			ft_printf("\t\t- show lives\n");
		if (env->verbose_level & VERBOSE_CYCLES_FLAG)
			ft_printf("\t\t- show cycles\n");
		if (env->verbose_level & VERBOSE_OPERATIONS_FLAG)
			ft_printf("\t\t- show operations (Params are NOT litteral ...)\n");
		if (env->verbose_level & VERBOSE_DEATH_FLAG)
			ft_printf("\t\t- show deaths\n");
		if (env->verbose_level & VERBOSE_PC_MOVEMENT_FLAG)
			ft_printf("\t\t- show PC movements (Except for jumps)\n");
	}
}
