/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 09:38:24 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 09:41:23 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_visu_draw_cycles(t_visu_env *venv, t_env *env)
{
	SDL_Rect	rect;
	SDL_Surface	*surf;
	SDL_Texture	*tex;
	char		*value;

	rect.x = 1225;
	rect.y = 50;
	if (!(value = ft_itoa(env->arena.cycles)))
		return (0);
	surf = TTF_RenderText_Blended(venv->font[NORMAL], value,
			*ft_get_color(venv, WHITE));
	tex = SDL_CreateTextureFromSurface(venv->renderer, surf);
	SDL_FreeSurface(surf);
	TTF_SizeText(venv->font[NORMAL], value, &rect.w, &rect.h);
	SDL_RenderCopy(venv->renderer, tex, NULL, &rect);
	SDL_DestroyTexture(tex);
	free(value);
	return (1);
}

void		ft_visu_draw_arena(t_visu_env *venv, t_env *env)
{
	ft_visu_draw_interface(venv);
	ft_visu_parse_instructions(venv, env);
	ft_visu_draw_instructions(venv, env);
	ft_visu_draw_process(venv, env, env->arena.process);
	ft_visu_draw_cycles(venv, env);
}

void		ft_visu_render_routine(t_env *env, t_visu_env *venv)
{
	ft_run_once(env);
	ft_visu_draw_arena(venv, env);
	SDL_RenderPresent(venv->renderer);
}

void		ft_visu_input_routine(t_env *env, t_visu_env *venv, int *mode,
		SDL_Event *e)
{
	(void)env;
	(void)venv;
	if (e->type == SDL_QUIT || (e->type == SDL_KEYDOWN && \
				e->key.keysym.sym == SDLK_ESCAPE))
		*mode = VISU_LEAVE;
	if (*mode != VISU_FINISH && e->type == SDL_KEYDOWN
			&& e->key.keysym.sym == SDLK_SPACE)
		*mode = (*mode == VISU_RUNNING ? VISU_PAUSED : VISU_RUNNING);
}

void		ft_visucheck_for_winner(t_env *env, t_visu_env *venv)
{
	t_champ	*highest;
	char	*str;

	highest = ft_get_champ(env->arena.last_live);
	str = ft_sprintf("Contestant %d, \"%s\", has won !", -highest->number,
				highest->header.prog_name);
	if (!str)
	{
		ft_dprintf(2, "serieux ca devient relou de proteger ces malloc de m\n");
		return ;
	}
	ft_display_winner(str, venv);
	free(str);
}
