/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:28:57 by toliver           #+#    #+#             */
/*   Updated: 2019/11/24 19:57:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_dump_env(t_env *env)
{
	ft_printf("env mode = %d\n", env->mode);
	ft_printf("env error = %d\n", env->error.value);
	ft_printf("flags = %d, en binaire : %b\n", env->flags, env->flags);
}

void		ft_dump_params(unsigned char param_nbr, t_param params[4])
{
	unsigned char	i;

	i = 0;
	while (i < param_nbr)
	{
		ft_printf("\tparam %hhu is : ", i);
		if (params[i].type == T_REG)
			ft_printf("a register ");
		else if (params[i].type == T_DIR)
			ft_printf("a direct ");
		else if (params[i].type == T_IND)
			ft_printf("an indirect ");
		else if (params[i].type == T_LAB)
			ft_printf("a label ");
		else
			ft_printf("AN UNKNOWN TYPE ");
		ft_printf("with value : ");
		if (params[i].type == T_LAB)
			ft_printf(">%s<\n", params[i].value.label);
		else
			ft_printf(">%d<\n", params[i].value.num); 
		i++;
	}
}

void		ft_dump_instructions(t_instruction *op)
{
	ft_printf("=== DUMP INSTRUCTIONS ===\n\n");
	while (op)
	{
		if (op->label)
			ft_printf("instruction is labeled : >%s< ", op->label);
		ft_printf("opcode: >%#.2x< ", op->opcode);
		ft_printf("works with >%hhu< params ", op_tab[op->opcode].params_number);
		ft_printf("and takes >%u< cycles\n", op_tab[op->opcode].cycles);
		ft_dump_params(op_tab[op->opcode].params_number, op->params);
		op = op->next;
	}
}

void		ft_dump_file(t_file *file)
{
	ft_printf("file name : %s\n", file->filename);
	ft_printf("file fd : %d\n", file->fd);
	ft_printf("file offset = %lld\n", file->offset);
	ft_printf("file .name : %s\n", file->name);
	ft_printf("file .comment : %s\n", file->comment);
	ft_printf("file actual line : %zu\n", file->line);
	ft_printf("file actual column : %zu\n", file->column);
	ft_dump_instructions(file->instructions);
}
