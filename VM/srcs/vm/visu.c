/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 04:40:19 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 05:15:09 by toliver          ###   ########.fr       */
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

int			ft_visu_instructions_init(t_visu_env *venv)
{
	int		i;

	if (!(venv->instructions = (char**)malloc(sizeof(char*) * MEM_SIZE)))
	{
		ft_dprintf(2, "Malloc failed !\n");
		return (0);
	}
	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(venv->instructions[i] = (char*)malloc(sizeof(char) * 3)))
		{
			ft_dprintf(2, "Malloc failed !\n");
			return (0);
		}
		ft_bzero(venv->instructions[i], 3);
		i++;
	}
	return (1);
}

int			ft_visu_init(t_visu_env *venv, t_env *env)
{
	(void)env;
	if (!(ft_visu_env_init(venv)))
		return (0);
	if (!(ft_visu_win_init(venv)))
		return (0);
	if (!(ft_visu_font_init(venv)))
		return (0);
	if (!(ft_visu_rect_init(venv)))
		return (0);
	if (!(ft_visu_instructions_init(venv)))
		return (0);
	ft_visu_color_init(venv);
	return (1);
}

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

void		ft_hex_to_buff(unsigned char value, char buf[3])
{
	buf[0] = value / 16 + (value / 16 < 10 ? '0' : 'a' - 10);
	buf[1] = value % 16 + (value % 16 < 10 ? '0' : 'a' - 10);
	buf[2] = 0;
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

void		ft_visu_draw_instructions(t_visu_env *venv, t_env *env)
{
	int			i;
	SDL_Rect	rect;
	SDL_Surface	*text;
	SDL_Texture	*text_tex;

	i = 0;
	while (i < MEM_SIZE)
	{
		rect = venv->instructions_rect[i];
		rect.x += 1;
		text = TTF_RenderText_Blended(venv->font[NORMAL], venv->instructions[i],
				*ft_get_color(venv,
					ft_get_color_from_player(env->arena.arena[i].writer)));
		text_tex = SDL_CreateTextureFromSurface(venv->renderer, text);
		TTF_SizeText(venv->font[NORMAL], venv->instructions[i], &rect.w,
				&rect.h);
		SDL_RenderCopy(venv->renderer, text_tex, NULL, &rect);
		SDL_FreeSurface(text);
		SDL_DestroyTexture(text_tex);
		i++;
	}
}

void		ft_visu_draw_process(t_visu_env *venv, t_env *env)
{
	t_process	*ptr;
	SDL_Rect	rect;
	SDL_Surface	*text;
	SDL_Texture	*text_tex;

	ptr = env->arena.process;
	while (ptr)
	{
		rect = venv->instructions_rect[ptr->pos];
		ft_set_color(venv,
				ft_get_color_from_player(env->arena.arena[ptr->pos].writer));
		SDL_RenderFillRect(venv->renderer, &rect);
		rect.x += 1;
		text = TTF_RenderText_Blended(venv->font[NORMAL],
			venv->instructions[ptr->pos], *ft_get_color(venv, BRIGHT_BLACK));
		text_tex = SDL_CreateTextureFromSurface(venv->renderer, text);
		TTF_SizeText(venv->font[NORMAL], venv->instructions[ptr->pos],
			&rect.w, &rect.h);
		SDL_RenderCopy(venv->renderer, text_tex, NULL, &rect);
		SDL_FreeSurface(text);
		SDL_DestroyTexture(text_tex);
		ptr = ptr->next;
	}
}

void		ft_visu_draw_arena(t_visu_env *venv, t_env *env)
{
	ft_visu_draw_interface(venv);
	ft_visu_parse_instructions(venv, env);
	ft_visu_draw_instructions(venv, env);
	ft_visu_draw_process(venv, env);
}

void		ft_free_instructions(t_visu_env *venv)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE && venv->instructions[i])
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
		{
			TTF_CloseFont(venv->font[i]);
			i++;
		}
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

void		ft_visu_quit(t_visu_env *venv)
{
	ft_free_instructions(venv);
	ft_close_ttf(venv);
	ft_close_sdl(venv);
}

void		ft_visu(t_env *env)
{
	t_visu_env		venv;
	int				running;
	SDL_Event		e;

	running = 1;
	if (!(ft_visu_init(&venv, env)))
	{
		ft_visu_quit(&venv);
		return ;
	}
	ft_visu_draw_arena(&venv, env);
	SDL_RenderPresent(venv.renderer);
	while (running)
	{
		ft_run_once(env);
		ft_visu_draw_arena(&venv, env);
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && \
						e.key.keysym.sym == SDLK_ESCAPE))
				running = 0;
		}
		SDL_RenderPresent(venv.renderer);
	}
	ft_visu_quit(&venv);
	return ;
}
