/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillfloat_deci_bigint2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 15:44:12 by toliver           #+#    #+#             */
/*   Updated: 2018/06/06 16:22:17 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				filldeciinit(t_splitd *num, int *bitsize, int *i,
		t_bigint *number)
{
	*bitsize = (num->islong) ? 63 : 52;
	*i = num->exp;
	number->number[967] = 1;
	return (1);
}

int				filldeci(t_bigint *number, t_splitd *num)
{
	int			i;
	int			bitread;
	int			bitsize;

	filldeciinit(num, &bitsize, &i, number);
	if (num->exp < -1)
	{
		while (i < -1)
		{
			mulnum(number, 10);
			multab(number, 5);
			i++;
		}
	}
	bitread = 1 + i;
	while (i <= bitsize)
	{
		mulnum(number, 10);
		if ((num->fra >> (bitsize - bitread)) & 1ull)
			addtab(number);
		bitread++;
		multab(number, 5);
		i++;
	}
	return (1);
}

int				write_bigint(t_bigint *number)
{
	int			value;

	if (!(number->rank == -1))
	{
		value = divtab(number, 10) + '0';
		write_bigint(number);
		number->fullnum[number->fullnumbuffer] = (char)value;
		number->fullnumbuffer++;
	}
	return (1);
}

int				copydecivalue(t_bigint *number)
{
	int			i;
	int			ii;

	write_bigint(number);
	i = number->comapos + 1;
	ii = number->comapos + 2;
	while (ii < 16457 && number->fullnum[ii])
	{
		number->fullnum[i] = number->fullnum[ii];
		i++;
		ii++;
	}
	number->fullnumbuffer--;
	while (number->fullnum[number->fullnumbuffer - 1] == '0')
		number->fullnumbuffer--;
	return (1);
}
