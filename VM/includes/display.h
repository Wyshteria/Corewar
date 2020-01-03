/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 23:56:03 by toliver           #+#    #+#             */
/*   Updated: 2020/01/03 16:40:19 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

//#include <ncurses.h>
//#define BRIGHT	0x8
//#define SMALL_SCREEN "screen is too small"

#define WINX	1600
#define WINY	1200

enum			e_color_type
{
	PLAYER1 = 1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	STANDARD_COLOR = 10,
};

enum			e_mode
{
	ENDED,
	RUNNING,
	TOO_SMALL,
};

enum			e_colors
{
	BLACK,
	BRIGHT_BLACK,
	RED,
	BRIGHT_RED,
	GREEN,
	BRIGHT_GREEN,
	YELLOW,
	BRIGHT_YELLOW,
	BLUE,
	BRIGHT_BLUE,
	MAGENTA,
	BRIGHT_MAGENTA,
	CYAN,
	BRIGHT_CYAN,
	WHITE,
	BRIGHT_WHITE
}

typedef struct		s_visu_env
{
	int				running;
	SDL_Window		*win;
	SDL_Renderer	*renderer;
}					t_visu_env;

#endif
