/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillfloat_roundinghexa.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 02:45:34 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int						roundinghexa2(t_splitd *num, char value[], int *i)
{
	while (value[(*i)] > 15 && *i >= 0)
	{
		if ((*i) > 0)
			value[(*i) - 1] += 1;
		else
		{
			num->exp -= 4;
			num->isrounded = 1;
			num->decisize--;
		}
		value[*i] -= 16;
		(*i)--;
	}
	return (1);
}

int						roundinghexa(t_splitd *num, char value[])
{
	int					i;

	if (value[num->prec + 1] < 8)
		return (0);
	else if (value[num->prec + 1] > 8)
		value[num->prec] += 1;
	else if (value[num->prec + 1] == 8)
	{
		i = 0;
		while (num->prec + 1 + i < 16 && value[num->prec + 1 + i] == 0)
			i++;
		if ((num->prec + 1 + i == 16 && !(value[num->prec] & 1))
				|| num->prec + 1 + i < 16)
			value[num->prec] += 1;
	}
	i = num->prec;
	roundinghexa2(num, value, &i);
	return (1);
}
