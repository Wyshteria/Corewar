/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillfloatinit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 02:44:20 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int					initdoublevalues(t_splitd *num, int islong, int sign)
{
	num->sign = sign;
	num->islong = islong;
	num->isnan = 0;
	num->isinf = 0;
	num->iszero = 0;
	num->issub = 0;
	return (1);
}

int					initdouble(t_splitd *num, double val)
{
	t_double		split;

	split.val = val;
	initdoublevalues(num, 0, split.value.sign);
	if (split.value.exp == DBL_MAX_EXP_VAL)
	{
		num->isinf = ((split.value.fra) ? 0 : 1);
		num->isnan = !num->isinf;
	}
	else if (split.value.exp == 0)
	{
		num->issub = ((split.value.fra) ? 1 : 0);
		num->exp = (num->issub) ? -1022 : 0;
		num->fra = (num->issub) ? split.value.fra : 0;
		num->iszero = !num->issub;
	}
	else
	{
		num->exp = split.value.exp - 1023;
		num->fra = split.value.fra + 0x10000000000000;
	}
	return (1);
}

int					initlongdoublesub(t_splitd *num, t_ldouble *split)
{
	num->exp = -16382;
	num->fra = split->value.fra + 0x8000000000000000 * split->value.intpart;
	num->issub = 1;
	return (1);
}

int					initlongdouble(t_splitd *num, long double val)
{
	t_ldouble		split;

	split.val = val;
	initdoublevalues(num, 1, split.value.sign);
	if (split.value.exp == 0)
	{
		if (!split.value.fra)
			num->iszero = 1;
		else
			initlongdoublesub(num, &split);
	}
	else if (split.value.exp == LDBL_MAX_EXP_VAL)
	{
		num->isnan = (split.value.fra) ? 1 : 0;
		num->isinf = !num->isnan;
	}
	else
	{
		num->exp = split.value.exp - 16383;
		num->fra = split.value.fra + 0x8000000000000000 * split.value.intpart;
	}
	return (1);
}

int					splitinit(t_arg *arg, t_splitd *num, t_penv *env)
{
	if (!(arg->length == 8))
		initdouble(num, arg->argument.d);
	else
		initlongdouble(num, arg->argument.ld);
	num->isrounded = 0;
	num->isuppercase = (*env->str <= 'Z') ? 1 : 0;
	num->type = (*env->str == 'f' || *env->str == 'F') ? ISDECI : num->type;
	num->type = (*env->str == 'e' || *env->str == 'E') ? ISEXP : num->type;
	num->type = (*env->str == 'g' || *env->str == 'G') ? ISSHORTEST : num->type;
	num->type = (*env->str == 'a' || *env->str == 'A') ? ISHEXA : num->type;
	if (num->type == ISHEXA && num->islong && !num->issub)
		num->fra |= 0x8000000000000000;
	return (1);
}
