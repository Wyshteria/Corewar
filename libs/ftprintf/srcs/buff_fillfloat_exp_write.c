/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillfloat_exp_write.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:30:43 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				charnumberset(t_bigint *number, t_arg *arg, t_splitd *num,
		int *charnumber)
{
	*charnumber = number->comapos;
	*charnumber += ((!(arg->prec == 0 && !(arg->flags & 2))) ? 1 : 0);
	*charnumber += arg->prec;
	*charnumber += ((num->sign || (arg->flags & 16)
				|| (arg->flags & 4)) ? 1 : 0);
	*charnumber += sizeofexponent(number->exp);
	return (1);
}

int				fucklanorme(t_bigint *number, t_penv *env, t_arg *arg)
{
	int			i;

	i = -1;
	while (++i < number->comapos)
		buff_fillwith(env, number->fullnum[i]);
	if (!(arg->prec == 0 && !(arg->flags & 2)) && i++ != -1)
		buff_fillwith(env, '.');
	while (arg->prec > 0 && i < number->fullnumbuffer && number->fullnum[i])
	{
		buff_fillwith(env, number->fullnum[i]);
		i++;
		arg->prec--;
	}
	while (arg->prec > 0)
	{
		buff_fillwith(env, '0');
		arg->prec--;
	}
	return (1);
}

int				float_writeexpoutput(t_bigint *number, t_splitd *num,
		t_penv *env, t_arg *arg)
{
	int			charnumber;
	int			padding;

	charnumberset(number, arg, num, &charnumber);
	padding = ((arg->width > charnumber) ? arg->width - charnumber : 0);
	if (padding && !(arg->flags & 32) && !(arg->flags & 8))
	{
		buff_fillwithnumber(env, ' ', padding);
		padding = 0;
	}
	putfloatsign(num->sign, arg->flags, env);
	if (padding && (arg->flags & 8))
	{
		buff_fillwithnumber(env, '0', padding);
		padding = 0;
	}
	fucklanorme(number, env, arg);
	putexponent(number->exp, num->isuppercase, env);
	if (padding)
		buff_fillwithnumber(env, ' ', padding);
	return (1);
}
