/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 09:42:13 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 23:50:40 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_free_instructions(t_visu_env *venv)
{
	int		i;

	i = 0;
	while (venv->instructions && i < MEM_SIZE && venv->instructions[i])
	{
		free(venv->instructions[i]);
		i++;
	}
	free(venv->instructions);
	free(venv->instructions_rect);
}

void		ft_close_ttf(t_visu_env *venv)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (venv->font[i])
			TTF_CloseFont(venv->font[i]);
		i++;
	}
	TTF_Quit();
}

void		ft_close_sdl(t_visu_env *venv)
{
	if (venv->renderer)
		SDL_DestroyRenderer(venv->renderer);
	if (venv->win)
		SDL_DestroyWindow(venv->win);
	SDL_Quit();
}

void		ft_free_fonts(t_visu_env *venv)
{
	int		i;
	int		j;

	i = 0;
	while (i < COLORLIMIT && venv->letters[i])
	{
		j = 0;
		while (venv->letters[i][j] && j < 256)
		{
			SDL_DestroyTexture(venv->letters[i][j]);
			j++;
		}
		free(venv->letters[i]);
		i++;
	}
}

void		ft_visu_quit(t_visu_env *venv)
{
	ft_free_fonts(venv);
	ft_free_instructions(venv);
	ft_close_ttf(venv);
	ft_close_sdl(venv);
}
