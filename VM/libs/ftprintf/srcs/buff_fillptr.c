/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 16:13:32 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			buff_fillptrinit(t_arg *arg, uintmax_t *value, int *length)
{
	*value = (uintmax_t)arg->argument.vptr;
	*length = ((*value) == 0 && arg->prec == 0) ? 0 :
		ft_uintmaxtlenbase((*value), 16);
	return (1);
}

int			buff_fillptr(t_penv *env, t_arg *arg)
{
	uintmax_t	value;
	int			length;
	int			numberofzeroes;
	int			lengthtotal;
	int			padding;

	buff_fillptrinit(arg, &value, &length);
	numberofzeroes = (length < arg->prec) ? arg->prec - length : 0;
	lengthtotal = length + numberofzeroes + 2;
	padding = (arg->width > lengthtotal) ? arg->width - lengthtotal : 0;
	if ((arg->flags & 8) && arg->prec == -1 && arg->width > 0
			&& length < arg->width)
	{
		numberofzeroes += (arg->width - 3 >= 0) ? arg->width - 3 : 0;
		padding -= numberofzeroes;
	}
	if (!(arg->flags & 32) && padding)
		buff_fillwithnumber(env, ' ', padding);
	buff_fillwithstr(env, "0x");
	buff_fillwithnumber(env, '0', numberofzeroes);
	if ((value == 0 && arg->prec) || value)
		buff_uimaxtoahexa(env, value);
	if ((arg->flags & 32) && padding)
		buff_fillwithnumber(env, ' ', padding);
	return (1);
}

int			buff_fillnptr(t_penv *env, t_arg *arg)
{
	if (arg->argument.iptr == NULL)
		return (0);
	*(arg->argument.iptr) = env->printflen + env->buffi;
	return (1);
}
