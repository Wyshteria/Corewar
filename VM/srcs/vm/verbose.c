/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 02:50:34 by toliver           #+#    #+#             */
/*   Updated: 2019/12/23 23:50:58 by toliver          ###   ########.fr       */
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

void		ft_verbose_op_params(t_arena *arena, t_process *process, t_opcode *op, int as_is_flag)
{
	int		i;

	i = 0;
	while (i < op->params_number)
	{
		if (op->params_types[i] == T_REG && (as_is_flag & 0b1000 >> i)) //&& !(op->opcode == LD && i == 1))
			ft_printf(" r%u", op->params[i]);
		else if (op->params_types[i] == T_REG)
			ft_printf(" %d", ft_get_value_from(op, process, arena, i));
		else
			ft_printf(" %d", op->params[i]);// anciennement nombre problematique
		i++;
	}
	if (op->opcode == ZJMP)
	{
		if (process->carry)
			ft_printf(" OK");
		else
			ft_printf(" FAILED");
	}
	else if (op->opcode == STI)
	{
		int32_t	value1;
		int32_t	value2;

		// au final faire une fonction pour les params supplementaires
		value1 = ft_get_value_from(op, process, arena, 1);
		value2 = ft_get_value_from(op, process, arena, 2);
		ft_printf("\n%8c -> store to %d + %d = %d (with pc and mod %d)", '|', value1, value2, value1 + value2, process->pos + (value1 + value2) % IDX_MOD);
	}
	else if (op->opcode == FORK || op->opcode == LFORK)
	{
		int32_t	value;

		value = (op->opcode == FORK) ? ((int16_t)op->params[0]) % IDX_MOD : op->params[0];
		ft_printf(" (%d)", (process->pos + value));
	}
	else if (op->opcode == LDI)
	{
		int32_t	value1;
		int32_t	value2;

		value1 = ft_get_value_from(op, process, arena, 0);
		value2 = ft_get_value_from(op, process, arena, 1);
		ft_printf("\n%8c -> load from %d + %d = %d (with pc and mod %d)", '|', value1, value2, value1 + value2, (process->pos + (value1 + value2) % IDX_MOD) % MEM_SIZE);
	}
	ft_printf("\n");
}

void		ft_verbose_op_params_bug(t_arena *arena, t_process *process, t_opcode *op, int as_is_flag)
{
	int		i;

	i = 0;
	while (i < op->params_number)
	{
		if ((op->params_types[i] == T_REG && (as_is_flag & (0b1000 >> i))) || (i != 1 && op->opcode == ST))
			ft_printf(" r%u", op->params[i]);
		else if (op->params_types[i] == T_REG && (i != 1 && op->opcode == ST))
			ft_printf(" %d", ft_get_value_from(op, process, arena, i));
		else if (op->params_types[i] == T_IND && (op->opcode == LD))
			ft_printf(" %d", ft_parse_value(arena, process->pos + op->params[i], 4));
		else
			ft_printf(" %d", op->params[i]);// anciennement nombre problematique
		i++;
	}
	ft_printf("\n");
}
void		ft_tmp_verboseparam(t_arena *arena, t_process *process, t_opcode *op)
{
	int		as_is;

	as_is = 0b1111;
	if (op->opcode == STI)
		as_is = 0b1000;
	else if(op->opcode == AND || op->opcode == OR || op->opcode == XOR)
		as_is = 0b0010;
	else if (op->opcode == LDI)
		as_is = 0b0010;
	else if (op->opcode == ST && op->params_types[1] == T_REG)
	{
		ft_verbose_op_params_bug(arena, process, op, as_is); // voir pokwa ca bug
		return ;
	}
	else if (op->opcode == LD && op->params_types[0] == T_IND)
	{
		ft_verbose_op_params_bug(arena, process, op, 0b0100);
		return ;
	}
	ft_verbose_op_params(arena, process, op, as_is);
}

void		ft_verbose_op(t_arena *arena, t_process *process, t_opcode *op)
{

	ft_printf("P %4d | %s", process->pid, op_tab[process->opcode_value].opcode);
	ft_tmp_verboseparam(arena, process, op);
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
		ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n", i, ptr->header.prog_size, ptr->header.prog_name, ptr->header.comment);
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


