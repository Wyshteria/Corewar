/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillfloat_exp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 06:15:36 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				sizeofexponent(int exp)
{
	int			len;

	len = ft_intmaxtlenbase(exp, 10);
	len = ((len < 2) ? 2 : len);
	len += 2;
	return (len);
}

int				putexponent(int exp, int isuppercase, t_penv *env)
{
	buff_fillwith(env, ((isuppercase) ? 'E' : 'e'));
	buff_fillwith(env, ((exp < 0) ? '-' : '+'));
	if (ft_intmaxtlenbase(exp, 10) < 2)
		buff_fillwith(env, '0');
	buff_imaxtoa(env, (intmax_t)exp);
	return (1);
}

int				exp_setting(t_bigint *number)
{
	int			i;

	number->exp = 0;
	while (number->fullnum[1] != '.')
	{
		number->fullnum[number->comapos] = number->fullnum[number->comapos - 1];
		number->fullnum[number->comapos - 1] = '.';
		number->comapos--;
		number->exp++;
	}
	while (number->fullnum[0] == '0')
	{
		number->fullnum[0] = number->fullnum[2];
		i = 2;
		while (i < number->fullnumbuffer && i < 16455)
		{
			number->fullnum[i] = number->fullnum[i + 1];
			i++;
		}
		number->fullnumbuffer--;
		number->exp--;
	}
	return (1);
}

int				buff_fillexp(t_splitd *num, t_bigint *number, t_penv *env,
		t_arg *arg)
{
	if (num->iszero)
	{
		number->fullnum[0] = '0';
		number->fullnum[1] = '.';
		number->fullnum[2] = '0';
		number->comapos = 1;
		number->fullnumbuffer = 3;
		number->exp = 0;
	}
	else
	{
		fill_bigint(number, num);
		exp_setting(number);
		float_rounding(number, &(arg->prec));
		if (number->comapos != 1)
		{
			number->fullnum[2] = number->fullnum[1];
			number->fullnum[1] = '.';
			number->exp++;
		}
	}
	float_writeexpoutput(number, num, env, arg);
	return (1);
}
