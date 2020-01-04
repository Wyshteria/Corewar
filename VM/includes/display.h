/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 23:56:03 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 05:19:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>

# define WINX	1600
# define WINY	1200

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
	BRIGHT_WHITE,
	COLORLIMIT
};

enum			e_police
{
	NORMAL,
	BOLD,
	ITALIC,
	BOLD_ITALIC,
	POLICELIMIT
};

typedef struct		s_visu_env
{
	int				running;
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Color		color[16];
	TTF_Font		*font[4];
	SDL_Rect		*instructions_rect;
	char			**instructions;
}					t_visu_env;

#endif
