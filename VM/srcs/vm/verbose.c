/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 02:50:34 by toliver           #+#    #+#             */
/*   Updated: 2019/12/27 22:21:41 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_verbose_flag(int flag)
{
	t_env	*env;

	env = ft_get_env();
	if ((env->flags & VERBOSE_FLAG) && (env->verbose_level & flag))
		return (1);
	return (0);
}

void		ft_verbose_op(t_arena *arena, t_process *process, t_opcode *op)
{
	(void)arena;
	(void)op;
	ft_printf("P %4d | %s", process->pid, op_tab[process->opcode_value].opcode);
}

void		ft_intro(t_env *env)
{
	int		i;
	t_champ	*ptr;

	ft_printf("Introducing contestants...\n");
	i = 1;
	ptr = env->champs;
	while (ptr)
	{
		ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n", i,
				ptr->header.prog_size, ptr->header.prog_name,
				ptr->header.comment);
		i++;
		ptr = ptr->next;
	}
}

void		ft_verbose_cycles(t_env *env)
{
	ft_printf("It is now cycle %d\n", env->arena.cycles);
}

void		ft_verbose_dump_arena(t_arena *arena)
{
	int		y;
	int		x;

	y = 0;
	while (y < 64)
	{
		x = 0;
		ft_printf("0x%.4x :", y * 64);
		while (x < 64)
		{
			ft_printf(" %.2x", arena->arena[y * 64 + x].value);
			x++;
		}
		ft_printf(" \n");
		y++;
	}
}

void		ft_verbose_move(t_opcode *op, t_process *process, t_arena *arena)
{
	int		i;

	ft_printf("ADV %d (0x%.4x -> 0x%.4x)", op->size, process->pos,
			(process->pos + op->size));
	i = 0;
	while (i < op->size)
	{
		ft_printf(" %.2x", arena->arena[((process->pos + i) % MEM_SIZE)].value);
		i++;
	}
	ft_printf(" \n");
}
