/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:18 by toliver           #+#    #+#             */
/*   Updated: 2020/01/02 08:17:46 by toliver          ###   ########.fr       */
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
		op->params_types[0] = op_tab[op->opcode].params[0];
	else
	{
		op->params_types[0] = ((op->encoding_byte & 0b11000000) >> 6);
		op->params_types[1] = ((op->encoding_byte & 0b110000) >> 4);
		op->params_types[2] = ((op->encoding_byte & 0b1100) >> 2);
		op->params_types[3] = (op->encoding_byte & 0b11);
		i = 0;
		while (i < op_tab[op->opcode].params_number)
		{
			if (op->params_types[i] == 3)
				op->params_types[i] = T_IND;
			if (!(op->params_types[i] & op_tab[op->opcode].params[i]))
				op->is_valid = 0;
			i++;
		}
	}
}

void		ft_exec_op(t_opcode *op, t_process *process, t_arena *arena)
{
	if (op_func[op->opcode] == NULL)
		ft_printf("(ne devrait pas arriver sauf sur 0)");
	else
	{
		if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG) && op->opcode != AFF)
			ft_verbose_op(arena, process, op);
		op_func[op->opcode](op, process, arena);
	}
}

void		ft_check_op_valid(t_opcode *op)
{
	int		i;

	if (!op->is_valid)
		return ;
	i = 0;
	while (i < op_tab[op->opcode].params_number)
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

void		ft_check_cycles(t_env *env)
{
	t_process	*ptr;
	t_process	*tmp;
	int			should_reset;
	int			lifetotal;

	should_reset = 0;
	lifetotal = 0;
	if (env->arena.cycles_to_die <= 0)
	{
		while (env->arena.process)
		{
			ptr = env->arena.process;
			if (ft_verbose_flag(VERBOSE_LIVES_FLAG))
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", ptr->pid, env->arena.cycles - ptr->last_live, env->arena.cycles_to_die);
			ft_kill_process(&env->arena, env->arena.process);
		}
	}
	ptr = env->arena.process;
//	if (ptr == NULL)
//		return ;
	while (ptr)
	{
		if (ptr->live_number == 0 && ptr->last_live <= env->arena.cycles - env->arena.cycles_to_die)
		{
			if (ft_verbose_flag(VERBOSE_LIVES_FLAG))
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", ptr->pid, env->arena.cycles - ptr->last_live, env->arena.cycles_to_die);
			tmp = ptr->next;
			ft_kill_process(&env->arena, ptr);
			ptr = tmp;
			continue;
		}
		lifetotal += ptr->live_number;
		ptr->live_number = 0;
		ptr = ptr->next;
	}
	if (lifetotal >= NBR_LIVE)
	{
		ft_decrease_cycle_to_die(&env->arena);
		env->arena.check_number = MAX_CHECKS;
	}
	else
		env->arena.check_number--;
	if (env->arena.check_number == 0)
	{
		ft_decrease_cycle_to_die(&env->arena);
		env->arena.check_number = MAX_CHECKS;
	}
	env->arena.actual_cycles_to_die = env->arena.cycles_to_die;
}

void		ft_check_for_winner(t_env *env)
{
	t_champ	*highest;

	highest = ft_get_champ(env->arena.last_live);

	if (!(env->flags & NCURSES_FLAG))
		ft_printf("Contestant %d, \"%s\", has won !\n", -highest->number, highest->header.prog_name);
	else
	{
		// faire qqch dans la vm ffs !
	}
}

void		ft_routine(t_env *env)
{
	t_process	*ptr;

	ptr = env->arena.process;
	while (ptr)
	{
		if (ptr->need_refresh == 1)
		{
			ft_get_process_infos(ptr, &env->arena);
			ptr->need_refresh = 0;
		}
		ptr->cycles_to_exec--;
		if (ptr->cycles_to_exec <= 0)
			ft_try_op(env, ptr);
		ptr = ptr->next;
	}
}

int			ft_run(t_env *env)
{
	ft_intro(env);
	while (1)
	{
		if ((env->flags & CYCLE_DUMP_FLAG) && env->arena.cycles % env->cycle_dump_cycles == 0)
			ft_verbose_dump_arena(&env->arena);
		if ((env->flags & DUMP_FLAG) && env->dump_cycles == env->arena.cycles)
		{
			ft_verbose_dump_arena(&env->arena);
			break ;
		}
		ft_increment_cycles(env);
		ft_routine(env);
		if (env->arena.actual_cycles_to_die <= 0)
			ft_check_cycles(env);
		if (env->arena.process == NULL)
		{
			ft_check_for_winner(env);
			break ;
		}
	}
	return (1);
}

void		ft_run_once(t_env *env)
{
	ft_increment_cycles(env);
	ft_routine(env);
	if (env->arena.actual_cycles_to_die <= 0)
		ft_check_cycles(env);
	if (env->arena.process == NULL)
		ft_check_for_winner(env);
}

int			main(int ac, char **av)
{
	t_env	env;

	ft_env_init(&env, av[0], ac - 1);
	if (!ft_parse_params(&env, av + 1))
		return (-1);
	ft_parse_champs(&env); // verifier qu'il y a bien un champion et qu'on en a pas trop
	if (!ft_init_arena(&env))
	{
		ft_free_env(&env);
		return (-1);
	}
	if (env.flags & NCURSES_FLAG)
		ft_visu(&env);
	else	
		ft_run(&env);
	ft_free_env(&env);
	return (0);
}
