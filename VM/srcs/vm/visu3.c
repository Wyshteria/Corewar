/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 09:33:32 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 09:51:04 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_set_color(t_visu_env *venv, int color)
{
	SDL_Color	*col;

	if (color < 0 || color >= COLORLIMIT)
		return ;
	col = &(venv->color[color]);
	SDL_SetRenderDrawColor(venv->renderer, col->r, col->g, col->b, col->a);
}

SDL_Color	*ft_get_color(t_visu_env *venv, int color)
{
	SDL_Color	*col;

	if (color < 0 || color >= COLORLIMIT)
		return (NULL);
	col = &(venv->color[color]);
	return (col);
}

void		ft_hex_to_buff(unsigned char value, char buf[3])
{
	buf[0] = value / 16 + (value / 16 < 10 ? '0' : 'a' - 10);
	buf[1] = value % 16 + (value % 16 < 10 ? '0' : 'a' - 10);
	buf[2] = 0;
}

int			ft_get_color_from_player(int player)
{
	if (player == -1)
		return (GREEN);
	else if (player == -2)
		return (BLUE);
	else if (player == -3)
		return (RED);
	else if (player == -4)
		return (CYAN);
	else if (player == 0)
		return (BRIGHT_GREEN);
	else
		return (WHITE);
}

void		ft_display_winner(char *value, t_visu_env *venv)
{
	SDL_Rect	rect;
	SDL_Surface	*surf;
	SDL_Texture	*tex;

	rect.x = 1225;
	rect.y = 75;
	if (!(surf = TTF_RenderText_Blended(venv->font[NORMAL], value,
			*ft_get_color(venv, WHITE))))
		return ;
	if (!(tex = SDL_CreateTextureFromSurface(venv->renderer, surf)))
	{
		SDL_FreeSurface(surf);
		return ;
	}
	SDL_FreeSurface(surf);
	TTF_SizeText(venv->font[NORMAL], value, &rect.w, &rect.h);
	SDL_RenderCopy(venv->renderer, tex, NULL, &rect);
	SDL_DestroyTexture(tex);
	SDL_RenderPresent(venv->renderer);
}
