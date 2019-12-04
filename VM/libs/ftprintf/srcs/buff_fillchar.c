/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 23:39:43 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				octsize(wchar_t nbr)
{
	int			i;

	i = 21;
	if (nbr == 0)
		return (1);
	while (!(nbr & (1 << (i - 1))))
		i--;
	if (i <= 7 && MB_CUR_MAX >= 1)
		return (1);
	else if (i <= 11 && MB_CUR_MAX >= 2)
		return (2);
	else if (i <= 16 && MB_CUR_MAX >= 3)
		return (3);
	else if (i <= 21 && MB_CUR_MAX == 4)
		return (4);
	return (0);
}

int				buff_fillchar(t_penv *env, t_arg *arg)
{
	if (arg->length == 3)
		return (buff_fillwchar(env, arg));
	else
		return (buff_fillc(env, arg));
}

int				buff_fillc(t_penv *env, t_arg *arg)
{
	if (arg->width > 1 && !(arg->flags & 32))
		buff_padding(env, arg, arg->width - 1);
	if (arg->length == 3)
		buff_fillwith(env, arg->argument.uc);
	else
		buff_fillwith(env, arg->argument.sc);
	if (arg->width > 1 && (arg->flags & 32))
		buff_padding(env, arg, arg->width - 1);
	return (1);
}

int				buff_fillwchar(t_penv *env, t_arg *arg)
{
	wint_t		value;
	int			size;

	size = octsize(arg->argument.wi);
	value = arg->argument.wi;
	if (arg->argument.wi > 0x10FFFF || arg->argument.wi < 0
			|| (arg->argument.wi >= 0xD800 && arg->argument.wi <= 0xDFFF))
		return (-1);
	else if (arg->argument.wi <= 127
			|| (arg->argument.wi <= 0xff && MB_CUR_MAX == 1))
		return (buff_fillc(env, arg));
	else
	{
		if (size < 1)
			return (-1);
		if (arg->width > size && !(arg->flags & 32))
			buff_fillwithnumber(env, ' ', arg->width - size);
		buff_putwchar(env, arg->argument.wi);
		if (arg->width > size && (arg->flags & 32))
			buff_fillwithnumber(env, ' ', arg->width - size);
		return (0);
	}
}

int				buff_putwchar(t_penv *env, wint_t unicode)
{
	char		buf[4];
	int			octset;
	wint_t		value;

	value = unicode;
	octset = octsize(value);
	while (octset != 1)
	{
		buf[octset - 1] = ((value & 0x3F) | 0x80);
		octset--;
		value = (value >> 6);
	}
	octset = octsize(unicode);
	buf[0] = value;
	while (--octset >= 0)
		buf[0] |= (0x80 >> octset);
	while (++octset < octsize(unicode))
		buff_fillwith(env, buf[octset]);
	return (1);
}
