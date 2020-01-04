/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 09:28:06 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 23:50:43 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

int			ft_visu_letter_color_init(t_visu_env *venv, int i)
{
	unsigned int	value;
	char			buf[3];
	SDL_Surface		*surf;

	value = 0;
	while (value < 256)
	{
		ft_hex_to_buff((unsigned char)value, buf);
		if (!(surf = TTF_RenderText_Blended(venv->font[NORMAL], buf,
						*ft_get_color(venv, i))))
		{
			ft_dprintf(2, "Couldn't allocate surface !\n");
			return (0);
		}
		if (!(venv->letters[i][value] =
					SDL_CreateTextureFromSurface(venv->renderer, surf)))
		{
			SDL_FreeSurface(surf);
			ft_dprintf(2, "Couldn't allocate texture !\n");
			return (0);
		}
		SDL_FreeSurface(surf);
		value++;
	}
	return (1);
}

int			ft_visu_letters_init(t_visu_env *venv)
{
	int		i;

	i = 0;
	while (i < COLORLIMIT)
	{
		if (!(venv->letters[i] =
					(SDL_Texture**)malloc(sizeof(SDL_Texture*) * 256)))
			return (0);
		ft_bzero(venv->letters[i], sizeof(SDL_Texture*) * 256);
		if (!(ft_visu_letter_color_init(venv, i)))
			return (0);
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
	if (!(ft_visu_letters_init(venv)))
		return (0);
	return (1);
}
