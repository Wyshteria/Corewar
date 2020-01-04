/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 08:27:00 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 09:28:01 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_visu_env_init(t_visu_env *visu_env)
{
	ft_bzero(visu_env, sizeof(t_visu_env));
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ft_dprintf(2, "Could not init SDL: %s\n", SDL_GetError());
		return (0);
	}
	if (TTF_Init() == -1)
	{
		ft_dprintf(2, "Could not init TTF: %s\n", TTF_GetError());
		return (0);
	}
	return (1);
}

int			ft_visu_win_init(t_visu_env *visu_env)
{
	if (!(visu_env->win = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, WINX, WINY, 0)))
	{
		ft_dprintf(2, "Could not create window\n");
		return (0);
	}
	if (!(visu_env->renderer = SDL_CreateRenderer(visu_env->win, -1,
					SDL_RENDERER_SOFTWARE)))
	{
		ft_dprintf(2, "Could not create renderer\n");
		return (0);
	}
	return (1);
}

void		ft_visu_color_init(t_visu_env *venv)
{
	venv->color[BLACK] = (SDL_Color){7, 54, 66, 255};
	venv->color[BRIGHT_BLACK] = (SDL_Color){0, 43, 54, 255};
	venv->color[RED] = (SDL_Color){220, 50, 47, 255};
	venv->color[BRIGHT_RED] = (SDL_Color){203, 75, 22, 255};
	venv->color[GREEN] = (SDL_Color){133, 153, 0, 255};
	venv->color[BRIGHT_GREEN] = (SDL_Color){88, 110, 117, 255};
	venv->color[YELLOW] = (SDL_Color){181, 137, 0, 255};
	venv->color[BRIGHT_YELLOW] = (SDL_Color){101, 123, 131, 255};
	venv->color[BLUE] = (SDL_Color){38, 139, 210, 255};
	venv->color[BRIGHT_BLUE] = (SDL_Color){131, 148, 150, 255};
	venv->color[MAGENTA] = (SDL_Color){211, 54, 130, 255};
	venv->color[BRIGHT_MAGENTA] = (SDL_Color){108, 113, 196, 255};
	venv->color[CYAN] = (SDL_Color){42, 161, 152, 255};
	venv->color[BRIGHT_CYAN] = (SDL_Color){147, 161, 161, 255};
	venv->color[WHITE] = (SDL_Color){238, 232, 213, 255};
	venv->color[BRIGHT_WHITE] = (SDL_Color){253, 246, 227, 255};
}

int			ft_visu_font_init(t_visu_env *venv)
{
	venv->font[NORMAL] = TTF_OpenFont("ressources/UbuntuMono-R.ttf", 14);
	venv->font[BOLD] = TTF_OpenFont("ressources/UbuntuMono-B.ttf", 14);
	venv->font[ITALIC] = TTF_OpenFont("ressources/UbuntuMono-RI.ttf", 14);
	venv->font[BOLD_ITALIC] = TTF_OpenFont("ressources/UbuntuMono-BI.ttf", 14);
	if (venv->font[NORMAL] == NULL || venv->font[BOLD] == NULL
			|| venv->font[ITALIC] == NULL
			|| venv->font[BOLD_ITALIC] == NULL)
	{
		ft_dprintf(2, "Couldn't load basic fonts !\n");
		return (0);
	}
	return (1);
}

int			ft_visu_rect_init(t_visu_env *venv)
{
	int		i;
	int		x;
	int		y;

	if (!(venv->instructions_rect =
				(SDL_Rect*)malloc(sizeof(SDL_Rect) * MEM_SIZE)))
	{
		ft_dprintf(2, "Malloc failed !\n");
		return (0);
	}
	i = 0;
	y = 0;
	while (y < 64)
	{
		x = 0;
		while (x < 64)
		{
			venv->instructions_rect[i] =
				(SDL_Rect){25 + x * 18, 25 + y * 18, 16, 16};
			x++;
			i++;
		}
		y++;
	}
	return (1);
}
