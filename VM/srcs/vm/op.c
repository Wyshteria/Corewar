/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/12/24 00:27:45 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_op    op_tab[17] =
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

void	(*op_func[17])(t_opcode*, t_process*, t_arena*) = 
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
	// copier toutes les operations
};

void		ft_ld(t_opcode *op, t_process *process, t_arena *arena)
{
	int		reg_number;
	int32_t	value;

	reg_number = op->params[1];
	if (op->params_types[0] == T_DIR)
		value = ft_get_value_from(op, process, arena, 0);
	else
		value = (int32_t)((int16_t)ft_parse_value(arena, process->pos + op->params[0], 4));
	*((uint32_t*)(process->reg[op->params[1] - 1].mem)) = value;
	if (value == 0)
		process->carry = 1;
	else
		process->carry = 0;
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
		ft_verbose_op(arena, process, op);
	ft_move_process(op, process, arena);
}

void		ft_st(t_opcode *op, t_process *process, t_arena *arena)
{
	int32_t	value;
	int32_t pos;
	value = ft_get_value_from(op, process, arena, 0);
	
	if (op->params_types[1] == T_REG)
		*(int32_t*)process->reg[op->params[1] - 1].mem = value;
	else
	{
		pos = ((op->params[1] % IDX_MOD) + process->pos) % MEM_SIZE;
		ft_write_in_arena(arena, pos, value, arena->arena[process->pos].writer);
	}
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
		ft_verbose_op(arena, process, op);
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
	process->carry = (result == 0 ? 1 : 0);
	*(int32_t*)process->reg[op->params[2] - 1].mem = result;
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
		ft_verbose_op(arena, process, op);
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
	process->carry = (result == 0 ? 1 : 0);
	*(int32_t*)process->reg[op->params[2] - 1].mem = result;
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
		ft_verbose_op(arena, process, op);
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
	*(int32_t*)process->reg[op->params[2] - 1].mem = result;
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
		ft_verbose_op(arena, process, op);
	ft_move_process(op, process, arena);
}

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
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
		ft_verbose_op(arena, process, op);
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
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
		ft_verbose_op(arena, process, op);
	ft_move_process(op, process, arena);
}

void		ft_zjmp(t_opcode *op, t_process *process, t_arena *arena)
{
	if (process->carry == 1)
	{
		process->pos = (process->pos + (op->params[0] % IDX_MOD)) % MEM_SIZE;
		if (process->pos < 0)
			process->pos = MEM_SIZE + process->pos;
		process->need_refresh = 1;
	}
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
		ft_verbose_op(arena, process, op);
	if (process->carry == 0)
		ft_move_process(op, process, arena);
}

void		ft_ldi(t_opcode *op, t_process *process, t_arena *arena)
{
	int32_t	value1;
	int32_t	value2;
	int32_t	value3;

	value1 = ft_get_value_from(op, process, arena, 0);
	value2 = ft_get_value_from(op, process, arena, 1);

	int32_t offset = (((value1 + value2) % IDX_MOD) + process->pos) % MEM_SIZE;
	if (offset < 0)
		offset = MEM_SIZE + offset;
	value3 = ft_parse_value(arena, offset, 4);
   	*(int32_t*)process->reg[op->params[2] - 1].mem = value3;
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
		ft_verbose_op(arena, process, op);
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
	ft_write_in_arena(arena, result, *(int32_t*)process->reg[op->params[0] - 1].mem, arena->arena[process->pos].writer);
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
		ft_verbose_op(arena, process, op);
	ft_move_process(op, process, arena);
	// should be working
}

void		ft_fork(t_opcode *op, t_process *process, t_arena *arena)
{
	int32_t	pos;

	pos = ((int16_t)op->params[0]) % IDX_MOD;
	ft_clone_process(arena, process, pos);
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
		ft_verbose_op(arena, process, op);
	ft_move_process(op, process, arena);
}

void		ft_lld(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un lld\n");
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
		ft_verbose_op(arena, process, op);
	ft_move_process(op, process, arena);
}

void		ft_lldi(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un lldi\n");
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
		ft_verbose_op(arena, process, op);
	ft_move_process(op, process, arena);
}

void		ft_lfork(t_opcode *op, t_process *process, t_arena *arena)
{
	ft_clone_process(arena, process, op->params[0]);
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
		ft_verbose_op(arena, process, op);
	ft_move_process(op, process, arena);
}

void		ft_aff(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un aff\n");
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
		ft_verbose_op(arena, process, op);
	ft_move_process(op, process, arena);
}

t_champ		*ft_get_champ(int32_t num)
{
	t_env	*env;
	t_champ	*ptr;

	env = ft_get_env();
	ptr = env->champs;
	while (ptr && ptr->number != num)
		ptr = ptr->next;
	return (ptr);
}

void		ft_live(t_opcode *op, t_process *process, t_arena *arena)
{
	int32_t	value;
	t_champ	*champ;

	value = ft_parse_value(arena, (process->pos + 1) % MEM_SIZE, 4);
	if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
		ft_verbose_op(arena, process, op);
	if ((champ = ft_get_champ(value)))
	{
		champ->live++;
		if (ft_verbose_flag(VERBOSE_LIVES_FLAG))
			//ft_printf("Player %d (%s) is said to be alive (testvalue to delete : %d)\n", -champ->number, champ->header.prog_name, *(int32_t*)process->reg[0].mem); // voir si c'est pas la value absolue
			ft_printf("Player %d (%s) is said to be alive\n", -champ->number, champ->header.prog_name);
	}
	process->live_number += 1;
	process->last_live = arena->cycles;
	ft_move_process(op, process, arena);
}
