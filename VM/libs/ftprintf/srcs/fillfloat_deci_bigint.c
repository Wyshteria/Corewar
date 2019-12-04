/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillfloat_deci_bigint.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:38:02 by toliver           #+#    #+#             */
/*   Updated: 2018/06/06 15:44:04 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				initbigint(t_bigint *number)
{
	int			i;

	number->rank = 0;
	i = 0;
	while (i < 968)
	{
		number->value[i] = 0;
		number->number[i] = 0;
		i++;
	}
	i = 0;
	while (i < 16457)
	{
		number->fullnum[i] = 0;
		i++;
	}
	number->fullnumbuffer = 0;
	return (1);
}

int				fillint(t_bigint *number, t_splitd *num)
{
	int			i;
	int			bitread;
	int			bitsize;

	bitsize = (num->islong) ? 63 : 52;
	i = num->exp;
	while (i > bitsize)
	{
		multab(number, 2);
		i--;
	}
	bitread = 0;
	while (i >= 0)
	{
		if (num->fra & (1ull << (bitsize - i)))
			addtab(number);
		bitread++;
		multab(number, 2);
		i--;
	}
	return (1);
}

int				copyintvalue(t_bigint *number)
{
	write_bigint(number);
	if (number->fullnumbuffer == 0)
	{
		number->fullnum[0] = '0';
		number->fullnumbuffer++;
	}
	return (1);
}

int				resetbigint(t_bigint *number)
{
	int			i;

	i = 0;
	number->rank = 0;
	while (i < 968)
	{
		number->value[i] = 0;
		number->number[i] = 0;
		i++;
	}
	return (1);
}

int				fill_bigint(t_bigint *number, t_splitd *num)
{
	int			testvalue;

	initbigint(number);
	number->value[967] = 1;
	fillint(number, num);
	copyintvalue(number);
	resetbigint(number);
	number->value[967] = 5;
	filldeci(number, num);
	number->comapos = number->fullnumbuffer;
	number->fullnum[number->fullnumbuffer] = '.';
	number->fullnumbuffer++;
	testvalue = number->fullnumbuffer;
	copydecivalue(number);
	return (1);
}
