/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillfloat_deci_write.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:34:54 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				putfloatsign(int sign, char flags, t_penv *env)
{
	if (sign)
		buff_fillwith(env, '-');
	else if (!sign && (flags & 4))
		buff_fillwith(env, ' ');
	else if (!sign && (flags & 16))
		buff_fillwith(env, '+');
	return (1);
}

int				float_writeoutput2(t_bigint *number, t_arg *arg, t_penv *env)
{
	int			i;

	i = -1;
	while (++i < number->comapos)
		buff_fillwith(env, number->fullnum[i]);
	if (!(arg->prec == 0 && !(arg->flags & 2)))
	{
		buff_fillwith(env, '.');
		i++;
	}
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

int				float_writeoutput(t_bigint *number, t_splitd *num, t_penv *env,
		t_arg *arg)
{
	int			charnumber;
	int			padding;

	charnumber = number->comapos;
	charnumber += ((!(arg->prec == 0 && !(arg->flags & 2))) ? 1 : 0);
	charnumber += ((num->sign || (arg->flags & 16) || (arg->flags & 4)) ?
			1 : 0) + arg->prec;
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
	float_writeoutput2(number, arg, env);
	if (padding)
		buff_fillwithnumber(env, ' ', padding);
	return (1);
}
