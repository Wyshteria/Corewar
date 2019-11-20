/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillutility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 23:38:57 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:11 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				buff_padding(t_penv *env, t_arg *arg, int width)
{
	int			i;

	i = -1;
	while (++i < width)
		buff_fillwith(env, (arg->flags & 8) ? '0' : ' ');
	return (1);
}

int				buff_fillwith(t_penv *env, char c)
{
	env->buff[env->buffi] = c;
	env->buffi++;
	buff_check(env);
	return (1);
}

int				buff_fillwithnumber(t_penv *env, char c, int i)
{
	while (i > 0)
	{
		buff_fillwith(env, c);
		i--;
	}
	return (1);
}

int				buff_fillwithstr(t_penv *env, char *str)
{
	while (*str)
	{
		buff_fillwith(env, *str);
		str++;
	}
	return (1);
}
