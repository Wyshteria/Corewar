/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 04:40:19 by toliver           #+#    #+#             */
/*   Updated: 2020/01/02 20:21:08 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
/*
   static void		ft_fill_process(t_arena *arena, WINDOW *main)
   {
   t_process	*ptr;
   int			x;
   int			y;

   ptr = arena->process;
   while (ptr)
   {
   if (arena->arena[ptr->pos].writer != 0)
   {
   wattron(main,
   COLOR_PAIR(-arena->arena[ptr->pos].writer) | A_REVERSE);
   if (ptr->opcode_value == LIVE && ptr->cycles_to_exec == 0)
   {
   wattron(main, A_BOLD);
   wattron(main,
   COLOR_PAIR(-arena->arena[ptr->pos].writer + 4) | A_REVERSE);
   }
   }
   else
   wattron(main, COLOR_PAIR(STANDARD_COLOR) | A_REVERSE);
   y = ptr->pos / arena->op_per_line;
   x = (ptr->pos - (y * arena->op_per_line)) * 3;
   mvwprintw(main, y + 1, x + 2, "%hh.2x", arena->arena[ptr->pos].value);
   if (arena->arena[ptr->pos].writer != 0)
   {
   wattroff(main,
   COLOR_PAIR(-(arena->arena[ptr->pos].writer)) | A_REVERSE);
   if (ptr->opcode_value == LIVE && ptr->cycles_to_exec == 0)
   {
   wattroff(main, A_BOLD);
   wattroff(main,
   COLOR_PAIR(-arena->arena[ptr->pos].writer + 4) | A_REVERSE);
   }
   }
   else
   wattroff(main, COLOR_PAIR(STANDARD_COLOR) | A_REVERSE);
   ptr = ptr->next;
   }
   }

   static void		ft_fill_arena(t_arena *arena, WINDOW *main) // attention meme nom !
   {
   int		x;
   int		y;
   int		i;

   y = 0;
   i = 0;
   wattron(main, COLOR_PAIR(STANDARD_COLOR));
   while (y < arena->line_number)
   {
   x = 0;
   while (x < arena->op_per_line)
   {
   if (arena->arena[i].writer != 0)
   wattron(main, COLOR_PAIR(-arena->arena[i].writer));
   else
   wattron(main, COLOR_PAIR(STANDARD_COLOR));
   mvwprintw(main, y + 1, x * 3 + 2, "%hh.2x", arena->arena[i].value);
   if (arena->arena[i].writer != 0)
   wattroff(main, COLOR_PAIR(-arena->arena[i].writer));
   else
   wattroff(main, COLOR_PAIR(STANDARD_COLOR));
   x++;
   i++;
   }
   y++;
   }
}

void		ft_ncurses_get_size(t_arena *arena)
{
	int		maxx;
	int		maxy;

	getmaxyx(stdscr, maxy, maxx);
	arena->maxx = maxx;
	arena->maxy = maxy;
	arena->op_per_line = (maxx + 1) / 3;
	while (MEM_SIZE % arena->op_per_line)
		(arena->op_per_line)--;
	arena->line_number = MEM_SIZE / arena->op_per_line;
	if (arena->line_number + 3 > maxy || (arena->op_per_line * 3 - 1 + 2 + 3) >
			maxx)
		arena->mode = TOO_SMALL;
	else
		arena->mode = RUNNING;
}

void		ft_ncurses_init_colors(void)
{
	start_color();
	init_pair(STANDARD_COLOR, COLOR_BLACK | BRIGHT, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_WHITE);
	init_pair(6, COLOR_BLUE, COLOR_WHITE);
	init_pair(7, COLOR_RED, COLOR_WHITE);
	init_pair(8, COLOR_CYAN, COLOR_WHITE);

}

void		ft_ncurses_init_params(void)
{
	noecho();
	curs_set(FALSE);
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	cbreak();
}

void		ft_fill_main_window(t_arena *arena, WINDOW *main)
{
	ft_fill_arena(arena, main);
	ft_fill_process(arena, main);
	wrefresh(main);
}

void		ft_ncurses_create_windows(t_arena *arena)
{
	if (arena->main == NULL)
		arena->main = newwin(arena->line_number + 2,
				(arena->op_per_line * 3) + 3, 0, 0);
	box(arena->main, 0, 0);
	ft_fill_main_window(arena, arena->main);
}

void		ft_ncurses_init(t_arena *arena)
{
	static int	first_run = 0;

	if (first_run == 0)
	{
		initscr();
		arena->mode = RUNNING;
		if (has_colors() == FALSE)
		{
			endwin();
			ft_printf("Your terminal does not support color\n");
			arena->mode = ENDED;
			return ;
		}
		ft_ncurses_init_colors();
		ft_ncurses_init_params();
		first_run = 1;
	}
	ft_ncurses_get_size(arena);
	refresh();
	if (arena->mode == RUNNING)
		ft_ncurses_create_windows(arena);
	else if (arena->mode == TOO_SMALL)
		mvprintw(arena->maxy / 2, (arena->maxx - ft_strlen(SMALL_SCREEN)) / 2,
				SMALL_SCREEN);
}

void		ft_ncurses_input(t_arena *arena)
{
	int		key;

	key = getch();
	if (key == 'q')
		arena->mode = ENDED;
}

void		ft_destroy_windows(t_arena *arena, int destroymain)
{
	if (arena->main && destroymain)
	{
		delwin(arena->main);
		arena->main = NULL;
	}
	if (arena->infos)
	{
		delwin(arena->infos);
		arena->infos = NULL;
	}
}

void		ft_check_resize(int signal)
{
	t_arena	*arena;

	if (signal == SIGWINCH)
	{
		endwin();
		clear();
		refresh();
		arena = &(ft_get_env()->arena);
		ft_ncurses_get_size(arena);
		//		resizeterm(arena->maxy, arena->maxx);
		if (arena->mode == TOO_SMALL)
		{
			ft_destroy_windows(arena, 0);
			clear();
			refresh();
			mvprintw(arena->maxy / 2,
					(arena->maxx - ft_strlen(SMALL_SCREEN)) / 2, SMALL_SCREEN);
		}
		else if (arena->mode == RUNNING)
		{
			clear();
			refresh();
			ft_ncurses_create_windows(arena);
		}
	}
}

void		ft_test(t_arena *arena)
{
	t_process	*process;

	process = arena->process;
	while (process)
	{
		process->pos = (process->pos + 1) % MEM_SIZE;
		process = process->next;
	}
}


void		ft_visu(t_env *env)
{
	t_arena	*arena;

	arena = &(env->arena);
	ft_ncurses_init(arena);
	while (arena->mode)
	{
		signal(SIGWINCH, ft_check_resize);
		ft_ncurses_input(arena);
		if (arena->mode != TOO_SMALL)
		{
			refresh();
			wrefresh(arena->main);
		}
		ft_run_once(env);
		ft_ncurses_init(arena);
	}
	endwin();
}


*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void		ft_visu(t_env *env)
{
	(void)env;
	SDL_Event		e;
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Could not init SDL: %s\n", SDL_GetError());
		return ;
	}
	if(TTF_Init() == -1) 
	{
		fprintf(stderr, "Could not init TTF: %s\n", TTF_GetError());
		return ;
	}
	while (SDL_PollEvent(&e))
	{
	}
	SDL_Window *screen = SDL_CreateWindow("My application",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			1600, 1200,
			0);
	if(!screen) {
		fprintf(stderr, "Could not create window\n");
		return ;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE);
	if(!renderer) {
		fprintf(stderr, "Could not create renderer\n");
		return ;
	}

	// draw part

	SDL_SetRenderDrawColor(renderer, 0, 43, 54, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 7, 54, 66, 255);

	SDL_Rect rect = {13,13,1174,1174};
	SDL_RenderFillRect(renderer, &rect);

	rect = (SDL_Rect){1198, 13, 390, 1174};
	SDL_RenderFillRect(renderer, &rect);

//	rect = (SDL_Rect){1225, 50, 16, 16};
//	SDL_RenderDrawRect(renderer, &rect);
	// FONT PART

	TTF_Font *police;
	SDL_Surface* texte;
	SDL_Texture* message; 

	police = TTF_OpenFont("ressources/UbuntuMono-R.ttf", 14);
	if (police)
	{
		texte = TTF_RenderText_Blended(police, "Wesh", (SDL_Color){0, 43, 54, 255});
		message = SDL_CreateTextureFromSurface(renderer, texte);
		TTF_SizeText(police, "Wesh", &rect.w, &rect.h);
		rect.x = 1226;
		rect.y = 50;

		SDL_RenderCopy(renderer, message, NULL, &rect);

		texte = TTF_RenderText_Blended(police, "11450 cycles", (SDL_Color){0, 43, 54, 255});
		message = SDL_CreateTextureFromSurface(renderer, texte);
		TTF_SizeText(police, "11450 cycles", &rect.w, &rect.h);
		rect.x = 1300;
		rect.y = 50;

		SDL_RenderCopy(renderer, message, NULL, &rect);
	}// penser a free la surface et la texture
	else
	{
		fprintf(stderr, "Could not create police\n");
	}
	// fill arena

	int		x;
	int		y;
	int		i;

	y = 0;
	i = 0;

	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
	while (y < 64)
	{
		x = 0;
		while (x < 64)
		{
			rect = (SDL_Rect){25 + x * 18, 25 + y * 18 ,16,16};
		//	SDL_RenderDrawRect(renderer, &rect);
	//		texte = TTF_RenderText_Blended(police, "0c", (SDL_Color){0, 43, 54, 255});
			texte = TTF_RenderText_Blended(police, "0c", (SDL_Color){255, 255, 255, 255});
			message = SDL_CreateTextureFromSurface(renderer, texte);
			TTF_SizeText(police, "0c", &rect.w, &rect.h);
			rect.x += 1;
			SDL_RenderCopy(renderer, message, NULL, &rect);

			x++;
			i++;
		}
		y++;
	}


	//
	SDL_RenderPresent(renderer);

	int		running = 1;
	while(running)
	{	
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && \
						e.key.keysym.sym == SDLK_ESCAPE))
				running = 0;
		}
	}

	// ttf clean
	TTF_CloseFont(police);
	TTF_Quit();

	// sdl clean
	SDL_DestroyWindow(screen);
	SDL_Quit();
	return ;
}
