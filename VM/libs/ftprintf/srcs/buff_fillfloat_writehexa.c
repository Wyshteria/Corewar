/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillfloat_writehexa.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 02:46:59 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int						writehexasetvalues(t_splitd *num, t_arg *arg,
						int *length, int *padding)
{
	(*length) = num->intsize + ((num->prec == -1) ? num->decisize : num->prec)
		+ (((num->prec != 0) || arg->flags & 2) ? 1 : 0) + 4
		+ numberlen(num->exp) +
		(((arg->flags & 16) || (arg->flags & 4) || num->sign) ? 1 : 0);
	*padding = (arg->width - (*length) > 0) ? arg->width - (*length) : 0;
	return (1);
}

int						writehexa_filldeci(t_splitd *num, t_penv *env,
						char value[], int *i)
{
	*i = (num->isrounded) ? -1 : 0;
	while (++(*i) <= num->decisize)
		buff_fillwith(env, value[*i]);
	return (1);
}

int						writehexa(t_splitd *num, t_penv *env, char value[],
		t_arg *arg)
{
	int					length;
	int					padding;
	int					i;

	writehexasetvalues(num, arg, &length, &padding);
	if (padding && !(arg->flags & 32) && !(arg->flags & 8))
		buff_fillwithnumber(env, ' ', padding);
	if (num->sign)
		buff_fillwith(env, '-');
	else if ((arg->flags & 16) || (arg->flags & 4))
		buff_fillwith(env, ((arg->flags & 16) ? '+' : ' '));
	buff_fillwithstr(env, ((num->isuppercase) ? "0X" : "0x"));
	if (padding && (arg->flags & 8))
		buff_fillwithnumber(env, '0', padding);
	buff_fillwith(env, ((num->isrounded) ? '1' : value[0]));
	if (((num->prec == -1) && num->decisize) || arg->flags & 2 || num->prec > 0)
		buff_fillwith(env, '.');
	if (num->prec > 0 || num->prec == -1)
		writehexa_filldeci(num, env, value, &i);
	if (arg->prec > num->decisize)
		buff_fillwithnumber(env, '0', arg->prec - num->decisize);
	buff_fillexponenthexa(env, num->isuppercase, num->exp);
	if (padding && (arg->flags & 32) && !(arg->flags & 8))
		buff_fillwithnumber(env, ' ', padding);
	return (1);
}
