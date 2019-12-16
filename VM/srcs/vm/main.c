/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:18 by toliver           #+#    #+#             */
/*   Updated: 2019/12/16 06:59:49 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// garder cette fonction de cote
void		ft_get_process_infos(t_process *process, t_arena *arena)
{
	process->opcode_value = arena->arena[process->pos].value;
	process->owner = arena->arena[process->pos].writer;
	if (process->opcode_value > 0 && process->opcode_value < 17)
		process->cycles_to_exec = op_tab[process->opcode_value].cycles;
	else
		process->cycles_to_exec = 1;
}
// celle la aussi
int			ft_add_process(t_arena *arena, int pos)
{
	t_process		*process;

	if (!(process = (t_process*)malloc(sizeof(t_process))))
		return (ft_arena_error(MALLOC_FAIL));
	ft_bzero(process, sizeof(t_process));
	process->pos = pos % MEM_SIZE;
	process->next = arena->process;
	arena->process = process;
	ft_get_process_infos(process, arena);
	process->pid = arena->pid;
	arena->pid += 1;
	return (1);
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
		ft_printf("* Player %d weighing %u bytes \"%s\" (\"%s\") !\n", i, ptr->header.prog_size, ptr->header.prog_name, ptr->header.comment);
		i++;
		ptr = ptr->next;
	}
}

int			ft_verbose_flag(int flag)
{
	t_env	*env;

	env = ft_get_env();
	if ((env->flags & VERBOSE_FLAG) && (env->verbose_level & flag))
		return (1);
	return (0);	
}

void		ft_increment_cycles(t_env *env)
{
	t_arena		*arena;
	t_process	*ptr;

	arena = &(env->arena);
	arena->cycles++;
	if (ft_verbose_flag(VERBOSE_CYCLES_FLAG))
	   ft_printf("It is now cycle %d\n", arena->cycles);
	ptr = arena->process;
	while (ptr)
	{
		ptr->cycles_to_exec--;
		ptr = ptr->next;
	}
}


void		ft_display_op(t_env *env, t_process *process, t_opcode *op)
{
	t_arena	*arena;
	int		i;

	arena = &(env->arena);
	ft_printf("P %4d | %s", process->pid, op_tab[process->opcode_value].opcode);
	i = 0;
	while (i < op->params_number)
	{
		ft_printf(" %c%u", (op->params_types[i] == T_REG ? 'r' : '\0'), op->params[i]);
		i++;
	}
	ft_printf("\n");
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

int			ft_parse_value(t_arena *arena, int pos, int size)
{
	union u_converter	value;
	int					i;

	i = 0;
	value.real_value = 0;
	while (i < size)
	{
		value.value[i] = arena->arena[(pos + i) % MEM_SIZE].value;
		i++;
	}
	if (size == 4)
		value.real_value = ft_swap(value.real_value);
	// verifier ici le jour ou jai un param plus gros :x

//	else if (size == 2)
//		value.real_value = ft_miniswap(value.real_value);
	return (value.real_value);	
}

void		ft_parse_op_params(t_opcode *op, t_process *process, t_arena *arena)
{
	int		i;
	int		param_size;

	i = 0;
	while (i < op->params_number)
	{
		param_size = ft_get_real_size(op->params_types[i], op->dir_two_bytes);
		op->params[i] = ft_parse_value(arena, process->pos + op->size, param_size);
		op->size += param_size;
		i++;
	}
}

void		ft_set_op_params_types(t_opcode *op)
{
	int		i;

	if (!op->need_encoding_byte)
		op->params_types[0] = op_tab[op->opcode].params[0];
	else
	{
		op->params_types[0] = ((op->encoding_byte & 0b11000000) >> 6);
		op->params_types[1] = ((op->encoding_byte & 0b110000) >> 4);
		op->params_types[2] = ((op->encoding_byte & 0b1100) >> 2);
		op->params_types[3] = (op->encoding_byte & 0b11);
		i = 0;
		while (i < 4)
		{
			if (op->params_types[i] == 3)
				op->params_types[i] = T_IND;
			if (!(op->params_types[i] & op_tab[op->opcode].params[i]))
				op->is_valid = 0;
			i++;
		}
	}
}


void		ft_print_move_process(t_opcode *op, t_process *process,
		t_arena *arena)
{
	int		i;

	ft_printf("ADV %d (0x%.4x -> 0x%.4x)", op->size, process->pos,
			(process->pos + op->size) % MEM_SIZE);
	i = 0;
	while (i < op->size)
	{
		ft_printf(" %.2x", arena->arena[(process->pos + i) % MEM_SIZE].value);
		i++;
	}
	ft_printf("\n");
}

void		ft_move_process(t_opcode *op, t_process *process, t_arena *arena)
{
	ft_print_move_process(op, process, arena);
	process->pos = (process->pos + op->size) % MEM_SIZE;
	ft_get_process_infos(process, arena);
}

void		ft_live(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un live\n");
	process->live_number += 1;
	ft_move_process(op, process, arena);
}

void		ft_ld(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un ld\n");
	ft_move_process(op, process, arena);
}

void		ft_st(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un st\n");
	ft_move_process(op, process, arena);
}

void		ft_add(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un add\n");
	ft_move_process(op, process, arena);
}
void		ft_sub(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un sub\n");
	ft_move_process(op, process, arena);
}

void		ft_and(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un and\n");
	ft_move_process(op, process, arena);
}

void		ft_or(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un or\n");
	ft_move_process(op, process, arena);
}

void		ft_xor(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un xor\n");
	ft_move_process(op, process, arena);
}

void		ft_zjmp(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un zjmp\n");
	ft_move_process(op, process, arena);
}

void		ft_ldi(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un ldi\n");
	ft_move_process(op, process, arena);
}
void		ft_sti(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un sti\n");
	ft_move_process(op, process, arena);
}

void		ft_fork(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un fork\n");
	ft_move_process(op, process, arena);
}

void		ft_lld(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un lld\n");
	ft_move_process(op, process, arena);
}

void		ft_lldi(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un lldi\n");
	ft_move_process(op, process, arena);
}

void		ft_lfork(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un lfork\n");
	ft_move_process(op, process, arena);
}

void		ft_aff(t_opcode *op, t_process *process, t_arena *arena)
{
	(void)op;
	(void)process;
	(void)arena;
	ft_printf("go coder ce que ca fait un aff\n");
	ft_move_process(op, process, arena);
}

void		ft_exec_op(t_opcode *op, t_process *process, t_arena *arena)
{
	if (op_func[op->opcode] == NULL)
		ft_printf("(ne devrait pas arriver sauf sur 0)");
	else
		op_func[op->opcode](op, process, arena);
	// verifier si l'op est 0 si ca fait le move
}

void		ft_parse_op(t_opcode *op, t_arena *arena, t_process *process)
{
	op->size = 1;
	if ((op->opcode = process->opcode_value) >= 17 || op->opcode == 0)
	{
		op->is_valid = 0;
		return ;
	}
	op->is_valid = 1;
	op->opcode_name = op_tab[op->opcode].opcode;
	op->params_number = op_tab[op->opcode].params_number;
	op->dir_two_bytes = op_tab[op->opcode].t_dir_is_two_bytes;
	if ((op->need_encoding_byte = op_tab[op->opcode].need_encoding_byte) == 1)
	{
		op->encoding_byte = arena->arena[((process->pos + 1) % MEM_SIZE)].value;
		op->size += 1;
	}
	ft_set_op_params_types(op);
	ft_parse_op_params(op, process, arena);
}

void		ft_print_op(t_opcode *op)
{
	ft_printf("==============================================\n");
	ft_printf("op opcode : %.2x | op name %s | op param number %d\n", op->opcode, op->opcode_name, op->params_number);
	ft_printf("op need an encoding byte : %s", op->need_encoding_byte ? "yes": "no\n");
	if (op->need_encoding_byte)
		ft_printf(" | encoding byte : %hhb\n", op->encoding_byte);
	ft_printf("params types: %d %d %d %d\n", op->params_types[0], op->params_types[1], op->params_types[2], op->params_types[3]);
	ft_printf("params : %d %d %d %d\n", op->params[0], op->params[1], op->params[2], op->params[3]);
	ft_printf("is a valid operation ? %s | ", op->is_valid ? "yes" : "no");
	ft_printf("its size is : %d\n", op->size);
	ft_printf("==============================================\n");
}

void		ft_try_op(t_env *env, t_process *process)
{
	t_opcode	opcode;
	
	ft_bzero(&opcode, sizeof(t_opcode));
	ft_parse_op(&opcode, &env->arena, process);
	// penser a tester le verbose
	//ft_print_op(&opcode);
	if (opcode.is_valid)
		ft_display_op(env, process, &opcode);
	if (opcode.is_valid)
		ft_exec_op(&opcode, process, &env->arena);
	else
		ft_move_process(&opcode, process, &env->arena);
	// penser a move
}

void		ft_check_for_action(t_env *env)
{
	t_process	*ptr;
	
	ptr = env->arena.process;
	while (ptr)
	{
		if (ptr->cycles_to_exec == 0)
			ft_try_op(env, ptr);
		ptr = ptr->next;
	}
}

int			ft_run(t_env *env)
{
	ft_intro(env);
	while (1)
	{
		ft_increment_cycles(env);
		ft_check_for_action(env);
		if (env->arena.cycles == 101)
			break;
		// check pour la vie et tout ca
	}
	return (1);
}

int			main(int ac, char **av)
{
	t_env	env;

	ft_env_init(&env, av[0], ac - 1);
	if (!ft_parse_params(&env, av + 1))
		return (-1);
	ft_parse_champs(&env);
	// verifier qu'il y a bien un champion et qu'on en a pas trop
	if (!ft_init_arena(&env))
	{
		// voir si ca free
		return (-1);
	}
//	ft_visu(&env);
	ft_run(&env);
//	ft_dump_arena(&env.arena);
//	ft_dump_env(&env);
	ft_free_env(&env);
	return (0);
}

// penser a set les numeros de players en negatif
