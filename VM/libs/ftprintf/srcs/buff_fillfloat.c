/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillfloat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:52:38 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int						buff_fillexponenthexa(t_penv *env, int up, int exp)
{
	buff_fillwith(env, ((up) ? 'P' : 'p'));
	buff_fillwith(env, ((exp >= 0) ? '+' : '-'));
	buff_imaxtoa(env, exp);
	return (1);
}

int						buff_fillhexalongd(t_splitd *num, t_penv *env,
		t_arg *arg)
{
	t_hexa				hex;
	char				value[16];

	if (!num->iszero)
	{
		hex.fra = num->fra;
		hexavaluesetd(hex, num, value);
	}
	num->intsize = 1;
	num->decisize = (num->iszero) ? 0 : 15;
	while (value[num->decisize] == 0 && num->decisize > 0)
		num->decisize--;
	if (num->prec != -1 && num->prec < num->decisize && !num->iszero)
	{
		roundinghexa(num, value);
		num->decisize = num->prec;
	}
	if (!num->iszero)
		setaswritable(value, 16, num->isuppercase);
	else
		value[0] = '0';
	writehexa(num, env, value, arg);
	return (1);
}

int						buff_fillhexad(t_splitd *num, t_penv *env, t_arg *arg)
{
	t_hexa				hex;
	char				value[16];

	if (!num->iszero)
	{
		hex.fra = num->fra << 8;
		hexavaluesetd(hex, num, value);
	}
	num->intsize = 1;
	num->decisize = (num->iszero) ? 0 : 15;
	while (value[num->decisize] == 0 && num->decisize > 0)
		num->decisize--;
	if (num->prec != -1 && num->prec < num->decisize && !num->iszero)
	{
		roundinghexa(num, value);
		num->decisize = num->prec;
	}
	if (!num->iszero)
		setaswritable(value, 16, num->isuppercase);
	else
		value[0] = '0';
	writehexa(num, env, value, arg);
	return (1);
}

int						buff_fillfloat(t_penv *env, t_arg *arg)
{
	static t_splitd		num;
	static t_bigint		number;

	splitinit(arg, &num, env);
	num.prec = arg->prec;
	num.width = arg->width;
	if (num.isinf || num.isnan)
		buff_fillerror(&num, env, arg);
	else if (num.type == ISHEXA)
		(num.islong) ? buff_fillhexalongd(&num, env, arg)
			: buff_fillhexad(&num, env, arg);
	else if (num.type == ISEXP)
		buff_fillexp(&num, &number, env, arg);
	else if (num.type == ISDECI)
		buff_fillfloatdeci(&num, &number, env, arg);
	return (1);
}
