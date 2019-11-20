/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillhexaoct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 23:45:26 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			buff_putprefix(t_penv *env, char c, int ishash)
{
	if (!ishash)
		return (1);
	else if ((c == 'o' || c == 'O') && ishash)
		buff_fillwith(env, '0');
	else if ((c == 'x' || c == 'X') && ishash)
		buff_fillwithstr(env, ((c == 'x') ? "0x" : "0X"));
	else if ((c == 'b' || c == 'B') && ishash)
		buff_fillwithstr(env, ((c == 'b') ? "0b" : "0B"));
	return (1);
}

int			buff_filloct(t_penv *env, t_arg *arg)
{
	uintmax_t	value;
	int			length;
	int			numberofzeroes;
	int			lengthtotal;
	int			padding;

	value = get_casteduintmaxt(arg);
	length = ft_uintmaxtlenbase(value, 8);
	length = (value == 0 && arg->prec == 0) ? 0 : length;
	numberofzeroes = (arg->prec > length) ? arg->prec - length : 0;
	numberofzeroes +=
		(!numberofzeroes && (arg->flags & 2) && (value || !length)) ? 1 : 0;
	lengthtotal = length + numberofzeroes;
	padding = (arg->width > lengthtotal) ? arg->width - lengthtotal : 0;
	if (!(arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	while (--numberofzeroes >= 0)
		buff_fillwith(env, '0');
	if (length > 0)
		buff_uimaxtoaoct(env, value);
	if ((arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	return (1);
}

int			valueset(t_arg *arg, uintmax_t *value, int *length,
		int *numberofzeroes)
{
	*value = get_casteduintmaxt(arg);
	*length = (*value == 0 && arg->prec == 0) ? 0
		: (int)ft_uintmaxtlenbase(*value, 16);
	*numberofzeroes = (arg->prec > *length) ? arg->prec - *length : 0;
	return (1);
}

int			buff_fillhexa(t_penv *env, t_arg *arg)
{
	uintmax_t	value;
	int			length;
	int			numberofzeroes;
	int			lengthtotal;
	int			padding;

	valueset(arg, &value, &length, &numberofzeroes);
	lengthtotal = length + numberofzeroes + ((arg->flags & 2 && value) ? 2 : 0);
	numberofzeroes += (arg->width > lengthtotal && (arg->flags & 8)) ?
		arg->width - lengthtotal : 0;
	padding = (arg->width > lengthtotal && !(arg->flags & 8)) ?
		arg->width - lengthtotal : 0;
	if (!(arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	if (value != 0)
		buff_putprefix(env, *env->str, arg->flags & 2);
	while (--numberofzeroes >= 0)
		buff_fillwith(env, '0');
	if (value != 0 || (value == 0 && arg->prec != 0))
		buff_uimaxtoahexa(env, value);
	if ((arg->flags & 32) && padding)
		buff_padding(env, arg, padding);
	return (1);
}
