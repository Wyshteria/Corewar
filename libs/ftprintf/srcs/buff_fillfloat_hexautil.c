/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillfloat_hexautil.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 02:49:34 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int						hexavaluesetd(t_hexa hex, t_splitd *num, char value[])
{
	int					i;
	int					ii;

	i = 7;
	ii = 0;
	while (((hex.byte[7] & 0xf0)) < 1)
	{
		hex.fra = hex.fra << 1;
		num->exp--;
	}
	while (i >= 0)
	{
		value[ii] = ((hex.byte[i] & 0xf0) >> 4);
		value[ii + 1] = hex.byte[i] & 0xf;
		ii += 2;
		i--;
	}
	return (1);
}

int						setaswritable(char value[], int size, int uppercase)
{
	int		i;

	i = 0;
	while (i < size)
	{
		value[i] += (value[i] <= 9) ? '0' : 'a' - 10 - 32 * uppercase;
		i++;
	}
	return (1);
}

int						numberlen(int number)
{
	int		i;

	i = 1;
	number = (number < 0) ? -number : number;
	while (number / 10)
	{
		number = number / 10;
		i++;
	}
	return (i);
}
