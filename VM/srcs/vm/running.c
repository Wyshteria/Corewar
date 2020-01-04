/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 04:52:22 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 04:53:44 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_kill_routine(t_env *env)
{
	t_process	*ptr;

	while (env->arena.process)
	{
		ptr = env->arena.process;
		if (ft_verbose_flag(VERBOSE_LIVES_FLAG))
			ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
					ptr->pid, env->arena.cycles - ptr->last_live,
					env->arena.cycles_to_die);
		ft_kill_process(&env->arena, env->arena.process);
	}
}

void		ft_check_routine(t_env *env, int *lifetotal)
{
	t_process	*ptr;
	t_process	*tmp;

	ptr = env->arena.process;
	while (ptr)
	{
		if (ptr->live_number == 0 && ptr->last_live <=
				env->arena.cycles - env->arena.cycles_to_die)
		{
			if (ft_verbose_flag(VERBOSE_LIVES_FLAG))
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
						ptr->pid, env->arena.cycles - ptr->last_live,
						env->arena.cycles_to_die);
			tmp = ptr->next;
			ft_kill_process(&env->arena, ptr);
			ptr = tmp;
			continue;
		}
		(*lifetotal) += ptr->live_number;
		ptr->live_number = 0;
		ptr = ptr->next;
	}
}

void		ft_check_cycles(t_env *env)
{
	int			lifetotal;

	lifetotal = 0;
	if (env->arena.cycles_to_die <= 0)
		ft_kill_routine(env);
	ft_check_routine(env, &lifetotal);
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
		if ((env->flags & CYCLE_DUMP_FLAG) &&
				env->arena.cycles % env->cycle_dump_cycles == 0)
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
