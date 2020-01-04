/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2020/01/04 05:06:01 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_op	g_op_tab[17] =
{
	{0, 0, {0}, 0, 0, 0, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
};

void	(*g_op_func[17])(t_opcode*, t_process*, t_arena*) =
{
	0,
	&ft_live,
	&ft_ld,
	&ft_st,
	&ft_add,
	&ft_sub,
	&ft_and,
	&ft_or,
	&ft_xor,
	&ft_zjmp,
	&ft_ldi,
	&ft_sti,
	&ft_fork,
	&ft_lld,
	&ft_lldi,
	&ft_lfork,
	&ft_aff,
};

void		ft_verbose_params_fuck_la_norme(t_opcode *op, t_process *proc)
{
	if (op->opcode == LDI)
		ft_printf("\n%8c -> load from %d + %d = %d (with pc and mod %d)", '|',
				op->params_parsed[0], op->params_parsed[1],
				op->params_parsed[0] + op->params_parsed[1], (proc->pos
					+ (op->params_parsed[0] + op->params_parsed[1]) % IDX_MOD));
	else if (op->opcode == LLDI)
		ft_printf("\n%8c -> load from %d + %d = %d (with pc %d)", '|',
				op->params_parsed[0], op->params_parsed[1], op->params_parsed[0]
				+ op->params_parsed[1], (proc->pos + (op->params_parsed[0]
						+ op->params_parsed[1])));
}

void		ft_verbose_params(t_opcode *op, t_process *proc, char r_display)
{
	int		i;

	i = 0;
	while (i < op->params_number)
	{
		if (op->params_types[i] == T_REG && (r_display & 0b1000 >> i))
			ft_printf(" r%d", op->params_parsed[i]);
		else
			ft_printf(" %d", op->params_parsed[i]);
		i++;
	}
	if (op->opcode == ZJMP)
		ft_printf(" %s", proc->carry ? "OK" : "FAILED");
	else if (op->opcode == FORK || op->opcode == LFORK)
		ft_printf(" (%d)", (proc->pos + op->params_parsed[1]));
	else if (op->opcode == STI)
		ft_printf("\n%8c -> store to %d + %d = %d (with pc and mod %d)", '|',
				op->params_parsed[1], op->params_parsed[2], op->params_parsed[1]
				+ op->params_parsed[2], (proc->pos + (op->params_parsed[1]
						+ op->params_parsed[2]) % IDX_MOD));
	else if (op->opcode == LDI || op->opcode == LLDI)
		ft_verbose_params_fuck_la_norme(op, proc);
	ft_printf("\n");
}
