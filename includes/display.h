/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 23:56:03 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 09:52:37 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>

# define WINX	1600
# define WINY	1200

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

enum			e_visu_mode
{
	VISU_LEAVE,
	VISU_RUNNING,
	VISU_PAUSED,
	VISU_FINISH,
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
	SDL_Texture		**letters[COLORLIMIT];
	SDL_Rect		*instructions_rect;
	char			**instructions;
}					t_visu_env;

typedef struct s_env		t_env;
typedef struct s_process	t_process;

int					ft_visu_env_init(t_visu_env *venv);
int					ft_visu_win_init(t_visu_env *venv);
void				ft_visu_color_init(t_visu_env *venv);
int					ft_visu_font_init(t_visu_env *venv);
int					ft_visu_rect_init(t_visu_env *venv);
int					ft_visu_instructions_init(t_visu_env *venv);
int					ft_visu_letter_color_init(t_visu_env *venv, int i);
int					ft_visu_letters_init(t_visu_env *venv);
int					ft_visu_init(t_visu_env *venv, t_env *env);
void				ft_set_color(t_visu_env *venv, int color);
SDL_Color			*ft_get_color(t_visu_env *venv, int color);
void				ft_hex_to_buff(unsigned char value, char buf[3]);
int					ft_get_color_from_player(int player);
void				ft_display_winner(char *value, t_visu_env *venv);
void				ft_visu_draw_interface(t_visu_env *venv);
void				ft_visu_parse_instructions(t_visu_env *venv, t_env *env);
void				ft_visu_draw_instructions(t_visu_env *venv, t_env *env);
int					ft_visu_draw_process(t_visu_env *venv, t_env *env,
		t_process *ptr);
int					ft_visu_draw_cycles(t_visu_env *venv, t_env *env);
void				ft_visu_draw_arena(t_visu_env *venv, t_env *env);
void				ft_visu_render_routine(t_env *env, t_visu_env *venv);
void				ft_visu_input_routine(t_env *env, t_visu_env *venv,
		int *mode, SDL_Event *e);
void				ft_visucheck_for_winner(t_env *env, t_visu_env *venv);
void				ft_visu_quit(t_visu_env *venv);
void				ft_free_fonts(t_visu_env *venv);
void				ft_close_sdl(t_visu_env *venv);
void				ft_close_ttf(t_visu_env *venv);
void				ft_free_instructions(t_visu_env *venv);
void				ft_visu_run(t_env *env, t_visu_env *venv);
void				ft_visu(t_env *env);

#endif
