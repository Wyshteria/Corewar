/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 04:40:19 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 23:50:42 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_visu_run(t_env *env, t_visu_env *venv)
{
	int			mode;
	SDL_Event	e;

	mode = VISU_RUNNING;
	ft_visu_draw_arena(venv, env);
	SDL_RenderPresent(venv->renderer);
	while (mode != VISU_LEAVE)
	{
		if (mode == VISU_RUNNING)
			ft_visu_render_routine(env, venv);
		while (SDL_PollEvent(&e))
			ft_visu_input_routine(env, venv, &mode, &e);
		if (env->arena.process == NULL && mode != VISU_LEAVE)
		{
			mode = VISU_FINISH;
			ft_visucheck_for_winner(env, venv);
		}
	}
}

void		ft_visu(t_env *env)
{
	t_visu_env		venv;

	if (!(ft_visu_init(&venv, env)))
	{
		ft_visu_quit(&venv);
		return ;
	}
	ft_visu_run(env, &venv);
	ft_visu_quit(&venv);
	return ;
}
