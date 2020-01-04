/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:37:44 by toliver           #+#    #+#             */
/*   Updated: 2020/01/03 22:38:05 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

void		ft_get_process_infos(t_process *process, t_arena *arena)
{
	process->opcode_value = arena->arena[process->pos].value;
	process->owner = arena->arena[process->pos].writer;
	if (process->opcode_value > 0 && process->opcode_value < 17)
	{
		process->cycles_to_exec = g_op_tab[process->opcode_value].cycles;
	}
	else
		process->cycles_to_exec = 1;
}

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

int			ft_clone_process(t_arena *arena, t_process *to_clone, int pos)
{
	t_process	*process;

	if (!(process = (t_process*)malloc(sizeof(t_process))))
	{
		ft_arena_error(MALLOC_FAIL);
		ft_free_env(ft_get_env());
		exit(-1);
	}
	ft_memcpy(process, to_clone, sizeof(t_process));
	process->pos = (pos + to_clone->pos) % MEM_SIZE;
	if (process->pos < 0)
		process->pos = MEM_SIZE + process->pos;
	process->pid = arena->pid;
	process->live_number = 0;
	arena->pid += 1;
	process->next = arena->process;
	arena->process = process;
	process->need_refresh = 1;
	return (1);
}

void		ft_move_process(t_opcode *op, t_process *process, t_arena *arena)
{
	if (process->pos < 0)
		process->pos = MEM_SIZE + process->pos;
	if (op->opcode > 0 && op->opcode <= 16
			&& ft_verbose_flag(VERBOSE_PC_MOVEMENT_FLAG))
		ft_verbose_move(op, process, arena);
	process->pos = (process->pos + op->size) % MEM_SIZE;
	process->need_refresh = 1;
}
