/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 19:32:52 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				mulnum(t_bigint *num, int value)
{
	int			i;
	int			retenue;

	i = 0;
	retenue = 0;
	while (i <= num->rank)
	{
		num->number[967 - i] = num->number[967 - i] * value + retenue;
		retenue = num->number[967 - i] / 100000000000000000;
		num->number[967 - i] %= 100000000000000000;
		i++;
		if (i > num->rank && retenue)
			num->rank++;
	}
	return (1);
}

int				multab(t_bigint *num, int value)
{
	int			i;
	int			retenue;

	i = 0;
	retenue = 0;
	while (i <= num->rank)
	{
		num->value[967 - i] = num->value[967 - i] * value + retenue;
		retenue = num->value[967 - i] / 100000000000000000;
		num->value[967 - i] %= 100000000000000000;
		i++;
		if (i > num->rank && retenue)
			num->rank++;
	}
	return (1);
}

int				divtab(t_bigint *num, int value)
{
	int			i;
	int			retval;

	retval = num->number[967] % value;
	num->number[967] /= value;
	num->number[967] += (num->number[966] % value) * 10000000000000000;
	i = 1;
	while (i <= num->rank)
	{
		num->number[967 - i] /= value;
		if (i < num->rank)
			num->number[967 - i] +=
				((num->number[967 - i - 1] % value) * 10000000000000000);
		i++;
	}
	if (num->number[967 - num->rank] == 0)
		num->rank--;
	return (retval);
}

int				addtab(t_bigint *num)
{
	int			i;
	int			retenue;

	i = 0;
	retenue = 0;
	while (i <= num->rank)
	{
		num->number[967 - i] = num->number[967 - i] +
			num->value[967 - i] + retenue;
		retenue = num->number[967 - i] / 100000000000000000;
		num->number[967 - i] %= 100000000000000000;
		i++;
		if (i >= num->rank && retenue != 0)
			num->rank++;
	}
	return (1);
}
