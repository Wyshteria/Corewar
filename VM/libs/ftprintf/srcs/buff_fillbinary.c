/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillbinary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 06:32:28 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int					buff_printdouble(t_penv *env, t_arg *arg)
{
	t_double		value;
	int				i;

	value.val = arg->argument.d;
	buff_fillwith(env, (value.value.sign) ? '1' : '0');
	i = -1;
	if (arg->flags & 2)
		buff_fillwith(env, ' ');
	while (++i < 11)
		buff_fillwith(env, ((value.value.exp >> (10 - i)) & 1ull) ? '1' : '0');
	if (arg->flags & 2)
		buff_fillwith(env, ' ');
	i = -1;
	while (++i < 52)
		buff_fillwith(env, ((value.value.fra >> (51 - i)) & 1ull) ? '1' : '0');
	return (1);
}

int					buff_printldouble(t_penv *env, t_arg *arg)
{
	t_ldouble		value;
	int				i;

	value.val = arg->argument.ld;
	buff_fillwith(env, (value.value.sign) ? '1' : '0');
	i = -1;
	if (arg->flags & 2)
		buff_fillwith(env, ' ');
	while (++i < 15)
		buff_fillwith(env, ((value.value.exp >> (14 - i)) & 1ull) ? '1' : '0');
	if (arg->flags & 2)
		buff_fillwith(env, ' ');
	buff_fillwith(env, (value.value.intpart) ? '1' : '0');
	if (arg->flags & 2)
		buff_fillwith(env, ' ');
	i = -1;
	while (++i < 63)
		buff_fillwith(env, ((value.value.fra >> (62u - i)) & 1ull) ? '1' : '0');
	return (1);
}

int					buff_printbits(t_penv *env, t_arg *arg, int length)
{
	int				i;

	i = length - 1;
	if (arg->length < 8)
	{
		while (i >= 0 && length - i > arg->prec)
		{
			if ((arg->argument.uimax >> i) & 1)
				buff_fillwith(env, '1');
			else
				buff_fillwith(env, '0');
			i--;
		}
	}
	else if (arg->length == 8)
		buff_printdouble(env, arg);
	else
		buff_printldouble(env, arg);
	return (1);
}

int					get_bitlen(t_arg *arg)
{
	int				i;

	i = 0;
	if (arg->length == 8)
		return (64 + (arg->flags & 2) ? 2 : 0);
	else if (arg->length == 9)
		return (80 + (arg->flags & 2) ? 2 : 0);
	else
	{
		if (arg->length == 0)
			return (32);
		else if (arg->length == 1)
			return (8);
		else if (arg->length == 2)
			return (16);
		else
			return (64);
	}
	while (arg->argument.uimax >> i)
		i++;
	if (i == 0)
		return (1);
	return (i);
}

int					buff_fillbinary(t_penv *env, t_arg *arg)
{
	int				length;
	int				numberofzeroes;
	int				lengthtotal;
	int				padding;

	length = (arg->argument.uimax == 0 && arg->prec == 0) ? 0 : get_bitlen(arg);
	numberofzeroes = (arg->prec > length) ? arg->prec - length : 0;
	lengthtotal = length + numberofzeroes
		+ ((arg->flags & 2 && arg->argument.uimax) ? 2 : 0);
	numberofzeroes += (arg->width > lengthtotal && (arg->flags & 8)) ?
		arg->width - lengthtotal : 0;
	padding = (arg->width > lengthtotal && !(arg->flags & 8)) ?
		arg->width - lengthtotal : 0;
	if (!(arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	if (arg->argument.uimax != 0)
		buff_putprefix(env, *env->str, arg->flags & 2);
	while (--numberofzeroes >= 0)
		buff_fillwith(env, '0');
	if (arg->argument.uimax != 0
			|| (arg->argument.uimax == 0 && arg->prec != 0))
		buff_printbits(env, arg, length);
	if ((arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	return (1);
}
