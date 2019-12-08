/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:18 by toliver           #+#    #+#             */
/*   Updated: 2019/12/08 12:22:58 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <ncurses.h>

void		ft_set_size(t_arena *arena, int maxx, int maxy)
{
	arena->maxx = maxx;
	arena->maxy = maxy;
	arena->op_per_line = (maxx + 1) / 3;
	while (MEM_SIZE % arena->op_per_line)
		(arena->op_per_line)--;
	arena->line_number = MEM_SIZE / arena->op_per_line;
//	ft_printf("maxx : %d maxy : %d\n", maxx, maxy);
//	ft_printf("line_number : %d op_per_line : %d\n", arena->line_number, arena->op_per_line);
//	if (arena->line_number > maxy)
//		ft_printf("not enough space to display the arena get a bigger terminal or try reducing character size\n");
}

void		ft_test(t_env *env)
{
//	int		lines;
//	int		columns;
	int		maxx;
	int		maxy;


	(void)env;
	initscr();
	noecho();
	curs_set(FALSE);

	getmaxyx(stdscr, maxy, maxx);
//	env->arena.maxx = maxx;
//	env->arena.maxy = maxy;
	ft_set_size(&env->arena, maxx, maxy);

		/*
	columns = (maxx + 1) / 3;
	while (MEM_SIZE % columns)
		columns--;
	lines = MEM_SIZE / columns;
	ft_printf("maxx : %d maxy : %d\n", maxx, maxy);
	ft_printf("lines : %d columns : %d\n", lines, columns);
	if (lines > maxy)
		ft_printf("not enough space to display the arena get a bigger terminal or try reducing character size\n");
	*/
	getmaxyx(stdscr, maxy, maxx);
	if (maxx != env->arena.maxx || maxy != env->arena.maxy)
		ft_set_size(&env->arena, maxx, maxy);
	endwin();
	ft_printf("line_number : %d op_per_line : %d\n", env->arena.line_number, env->arena.op_per_line);
/*
	while(1) {
	 getmaxyx(stdscr, maxy, maxx);
 clear();
 mvprintw(y, x, "o");
 refresh();
 usleep(20000);
 x++;
 if (x > maxx)
 {
	x = 0;
	y++;
 }
 if (y > maxy)
	 y = 0;
 }
	*/
}

int			ft_arena_error(int error)
{
	ft_dprintf(2, "%s: ", ft_get_env()->prog_name);
	if (error == NOT_ENOUGH_SPACE)
		ft_dprintf(2, "Not enough space in arena to place all champions\n");
	return (0);
}


void			ft_dump_arena(t_arena *arena)
{
	int			i;
	t_process	*ptr;
	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%.2x(%d) ", arena->arena[i].value, arena->arena[i].writer);
		i++;
	}
	ft_printf("\n");
	ptr = arena->process;
	while (ptr)
	{
		ft_printf("process:\n");
		ft_printf("\tpos = %d\n", ptr->pos);
		ft_printf("\towner = %d\n", ptr->owner);
		ptr = ptr->next;
	}
}

int			ft_add_process(t_arena *arena, int owner, int pos)
{
	t_process		*process;

	if (!(process = (t_process*)malloc(sizeof(t_process))))
		return (ft_arena_error(MALLOC_FAIL));
	process->pos = pos;
	process->owner = owner;
	process->next = arena->process;
	arena->process = process;
	return (1);
}

void		ft_fill_arena(t_arena *arena, t_champ *champ, int pos)
{
	int		i;

	i = 0;
	while (i < (int)champ->header.prog_size)
	{
		arena->arena[pos + i].value = champ->content[i];
		arena->arena[pos + i].writer = champ->number;
		i++;
	}
}
int			ft_init_arena(t_env *env)
{
	unsigned int	total_size;
	t_champ			*ptr;
	int				champ_number;
	int				space_between;

	ptr = env->champs;
	total_size = 0;
	champ_number = 0;
	while (ptr)
	{
		total_size += ptr->header.prog_size;
		champ_number++;
		ptr = ptr->next;
	}
	if (total_size >= MEM_SIZE)
		return (ft_arena_error(NOT_ENOUGH_SPACE)); 
	space_between = (MEM_SIZE - total_size) / champ_number;
	ptr = env->champs;
	

	int				actualpos;

	actualpos = 0;
	ptr = env->champs;
	while (ptr)
	{
		if (!(ft_add_process(&env->arena, ptr->number, actualpos)))
			return (0);
		ft_fill_arena(&env->arena, ptr, actualpos);
		actualpos += (ptr->header.prog_size + space_between);
		ptr = ptr->next;
	}
	ft_test(env);
//	ft_dump_arena(&env->arena);
	return (1);
}

int			main(int ac, char **av)
{
	t_env	env;

	ft_env_init(&env, av[0], ac - 1);
	if (!ft_parse_params(&env, av + 1))
		return (-1);
	ft_parse_champs(&env);
	// verifier qu'il y a bien un champion
	if (ft_init_arena(&env))
	{
		ft_printf("working !\n");
	}
//	ft_dump_env(&env);
	ft_free_env(&env);
	return (0);
}
