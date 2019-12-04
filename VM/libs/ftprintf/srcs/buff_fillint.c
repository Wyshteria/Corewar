/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 16:14:26 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			buff_putsign(t_penv *env, intmax_t value, int plus, int space)
{
	if (value < 0)
		buff_fillwith(env, '-');
	else if (plus)
		buff_fillwith(env, '+');
	else if (space)
		buff_fillwith(env, ' ');
	return (1);
}

int			buff_fillint_init(t_arg *arg, intmax_t *value, int *length)
{
	*value = get_castedintmaxt(arg);
	*length = ((*value) == 0 && arg->prec == 0) ? 0 :
		(int)ft_intmaxtlenbase((*value), 10);
	return (1);
}

int			buff_fillint(t_penv *env, t_arg *arg)
{
	intmax_t	value;
	int			length;
	int			numberofzeroes;
	int			lengthtotal;
	int			padding;

	buff_fillint_init(arg, &value, &length);
	numberofzeroes = (arg->prec > length) ? arg->prec - length : 0;
	lengthtotal = length + numberofzeroes +
		(((arg->flags & 16) || (arg->flags & 4) || value < 0) ? 1 : 0);
	numberofzeroes += (arg->width > lengthtotal && (arg->flags & 8)) ?
		arg->width - lengthtotal : 0;
	padding = (arg->width > lengthtotal && !(arg->flags & 8)) ?
		arg->width - lengthtotal : 0;
	if (!(arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	buff_putsign(env, value, arg->flags & 16, arg->flags & 4);
	while (--numberofzeroes >= 0)
		buff_fillwith(env, '0');
	if (value != 0 || (value == 0 && arg->prec != 0))
		buff_imaxtoa(env, value);
	if ((arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	return (1);
}

int			buff_filluint(t_penv *env, t_arg *arg)
{
	uintmax_t	value;
	int			length;
	int			numberofzeroes;
	int			lengthtotal;
	int			padding;

	value = get_casteduintmaxt(arg);
	length = (value == 0 && arg->prec == 0) ?
		0 : (int)ft_uintmaxtlenbase(value, 10);
	numberofzeroes = (arg->prec > length) ? arg->prec - length : 0;
	lengthtotal = length + numberofzeroes;
	numberofzeroes += (arg->width > lengthtotal && (arg->flags & 8)) ?
		arg->width - lengthtotal : 0;
	padding = (arg->width > lengthtotal && !(arg->flags & 8)) ?
		arg->width - lengthtotal : 0;
	if (!(arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	while (--numberofzeroes >= 0)
		buff_fillwith(env, '0');
	if (value != 0 || (value == 0 && arg->prec != 0))
		buff_uimaxtoa(env, value);
	if ((arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	return (1);
}
