/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 04:40:19 by toliver           #+#    #+#             */
/*   Updated: 2019/12/09 14:26:29 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		ft_fill_process(t_arena *arena, WINDOW *main)
{
	t_process	*ptr;
	int			x;
	int			y;


	ptr = arena->process;
	while (ptr)
	{
		if (arena->arena[ptr->pos].writer != 0)
			wattron(main, COLOR_PAIR(-arena->arena[ptr->pos].writer) | A_REVERSE);
		else
			wattron(main, COLOR_PAIR(STANDARD_COLOR) | A_REVERSE);
		y = ptr->pos / arena->op_per_line;
		x = (ptr->pos - (y * arena->op_per_line)) * 3;
		mvwprintw(main, y + 1, x + 2, "%hh.2x", arena->arena[ptr->pos].value);
		if (arena->arena[ptr->pos].writer != 0)
			wattroff(main, COLOR_PAIR(-(arena->arena[ptr->pos].writer)) | A_REVERSE);
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
	if (arena->line_number + 3 > maxy || (arena->op_per_line * 3 - 1 + 2 + 3) > maxx) // essayer de resoudre le soucis de resize
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
		arena->main = newwin(arena->line_number + 2, (arena->op_per_line * 3) + 3, 0, 0);
	box(arena->main, 0, 0);
	ft_fill_main_window(arena, arena->main);
}

void		ft_ncurses_init(t_arena *arena)
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
	ft_ncurses_get_size(arena);
	refresh();
	if (arena->mode == RUNNING)
		ft_ncurses_create_windows(arena);
	else if (arena->mode == TOO_SMALL)
		mvprintw(arena->maxy/2,(arena->maxx-ft_strlen(SMALL_SCREEN))/2, SMALL_SCREEN);
}

void		ft_ncurses_input(t_arena *arena)
{
	int		key;

	key = getch();
	if (key == 'q')
		arena->mode = ENDED;
}

void		ft_destroy_windows(t_arena *arena)
{
	if (arena->main)
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
		resizeterm(arena->maxy, arena->maxx);
		if (arena->mode == TOO_SMALL)
		{
			ft_destroy_windows(arena);
			clear();
			refresh();
			mvprintw(arena->maxy/2,(arena->maxx-ft_strlen(SMALL_SCREEN))/2, SMALL_SCREEN);
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
		usleep(10000);
		refresh();
		wrefresh(arena->main);
//		ft_fill_process(arena, arena->main);
//		ft_test(arena);
//		ft_do_process(arena);
	}
	endwin();
}
