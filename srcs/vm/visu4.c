/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 09:36:29 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 09:38:13 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_visu_draw_interface(t_visu_env *venv)
{
	SDL_Rect rect;

	ft_set_color(venv, BRIGHT_BLACK);
	SDL_RenderClear(venv->renderer);
	ft_set_color(venv, BLACK);
	rect = (SDL_Rect){13, 13, 1174, 1174};
	SDL_RenderFillRect(venv->renderer, &rect);
	rect = (SDL_Rect){1198, 13, 390, 1174};
	SDL_RenderFillRect(venv->renderer, &rect);
}

void		ft_visu_parse_instructions(t_visu_env *venv, t_env *env)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_hex_to_buff(env->arena.arena[i].value, venv->instructions[i]);
		i++;
	}
}

void		ft_visu_draw_instructions(t_visu_env *venv, t_env *env)
{
	int			i;
	SDL_Rect	rect;

	i = 0;
	while (i < MEM_SIZE)
	{
		rect = venv->instructions_rect[i];
		rect.x += 1;
		TTF_SizeText(venv->font[NORMAL], venv->instructions[i], &rect.w,
				&rect.h);
		SDL_RenderCopy(venv->renderer,
				venv->letters[
				ft_get_color_from_player(env->arena.arena[i].writer)]
				[env->arena.arena[i].value], NULL, &rect);
		i++;
	}
}

static int	ft_visu_niklanorm(SDL_Surface *tofree)
{
	SDL_FreeSurface(tofree);
	return (0);
}

int			ft_visu_draw_process(t_visu_env *venv, t_env *env, t_process *ptr)
{
	SDL_Rect	rect;
	SDL_Surface	*text;
	SDL_Texture	*text_tex;

	while (ptr)
	{
		rect = venv->instructions_rect[ptr->pos];
		ft_set_color(venv,
				ft_get_color_from_player(env->arena.arena[ptr->pos].writer));
		SDL_RenderFillRect(venv->renderer, &rect);
		rect.x += 1;
		if (!(text = TTF_RenderText_Blended(venv->font[NORMAL],
			venv->instructions[ptr->pos], *ft_get_color(venv, BRIGHT_BLACK))))
			return (0);
		if (!(text_tex = SDL_CreateTextureFromSurface(venv->renderer, text)))
			return (ft_visu_niklanorm(text));
		TTF_SizeText(venv->font[NORMAL], venv->instructions[ptr->pos],
				&rect.w, &rect.h);
		SDL_RenderCopy(venv->renderer, text_tex, NULL, &rect);
		SDL_FreeSurface(text);
		SDL_DestroyTexture(text_tex);
		ptr = ptr->next;
	}
	return (1);
}
