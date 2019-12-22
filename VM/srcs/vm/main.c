/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:18 by toliver           #+#    #+#             */
/*   Updated: 2019/12/22 06:15:33 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_increment_cycles(t_env *env)
{
	t_arena		*arena;
	t_process	*ptr;

	arena = &(env->arena);
	arena->cycles++;
	arena->actual_cycles_to_die--;
	if (ft_verbose_flag(VERBOSE_CYCLES_FLAG))
		ft_verbose_cycles(env);
	ptr = arena->process;
	while (ptr)
	{
		ptr->cycles_to_exec--;
		ptr = ptr->next;
	}
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
		op->params[i] = ft_parse_value(arena, (process->pos + op->size) % MEM_SIZE, param_size);
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
		if (ft_verbose_flag(VERBOSE_OPERATIONS_FLAG))
			ft_verbose_op(ft_get_env(), process, op);
		op_func[op->opcode](op, process, arena);
	}
	// verifier si l'op est 0 si ca fait le move
}

void		ft_check_op_valid(t_opcode *op)
{
	int		i;

	if (!op->is_valid)
	   return;	
	i = 0;
	while (i < op_tab[op->opcode].params_number)
	{
		if ((op->params_types[i] == T_IND ||
				(op->params_types[i] == T_DIR && op->dir_two_bytes)) 
				&& op->params[i] & 0x8000)
			op->params[i] = (int32_t)((int16_t)op->params[i]);
		if (op->params_types[i] == T_REG && (op->params[i] > REG_NUMBER || op->params[i] == 0))
			op->is_valid = 0; // NOT SURE ABOUT THAT
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

void		ft_check_cycles(t_env *env)
{
	t_process	*ptr;
	t_process	*tmp;

	ft_printf("---------CHECK !------------\n");
	if (env->arena.cycles_to_die <= 0)
	{
		// kill all process but one;
	}
	ptr = env->arena.process;
	while (ptr)
	{
		if (ptr->live_number == 0)
		{
			ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", ptr->pid, env->arena.cycles - ptr->last_live, env->arena.cycles_to_die);
		}
		if (ptr->live_number >= NBR_LIVE)
		{
			env->arena.cycles_to_die -= CYCLE_DELTA;
			env->arena.check_number = 0;
		}
		else
		{
			env->arena.check_number++;
			if (env->arena.check_number >= 10)
				ft_printf("too many checks !\n");
		}
		ptr->live_number = 0;
		ptr = ptr->next;	
	}
	env->arena.actual_cycles_to_die = env->arena.cycles_to_die;
	(void)tmp;
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
			break;
		}
		ft_increment_cycles(env);
		ft_check_for_action(env);
		if (env->arena.actual_cycles_to_die == 0)
			ft_check_cycles(env);
		// check for winner if no more process
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
	ft_run(&env);
	ft_free_env(&env);
	return (0);
}

