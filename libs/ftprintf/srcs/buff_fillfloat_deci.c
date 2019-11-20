/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_filldeci.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 02:23:40 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				mustround(t_bigint *number, int prec, int numberofdeci)
{
	int			i;

	i = number->comapos + prec + 2;
	while (i < (numberofdeci + number->comapos) && number->fullnum[i] == '0')
		i++;
	if (i < numberofdeci + number->comapos)
		return (1);
	i = number->comapos + prec;
	if ((prec != 0 && number->fullnum[i] % 2 == 1) || (prec == 0
				&& number->fullnum[number->comapos - 1] % 2 == 1))
		return (1);
	return (0);
}

int				float_rounding_pastcoma(int retenue, int i, t_bigint *number)
{
	i--;
	while (i >= 0 && retenue)
	{
		number->fullnum[i] += retenue;
		retenue = (number->fullnum[i] <= '9') ? 0 : 1;
		number->fullnum[i] = (retenue) ? number->fullnum[i] - 10
			: number->fullnum[i];
		i--;
	}
	if (i < 0 && retenue)
	{
		i = number->fullnumbuffer - 1;
		while (i >= 0)
		{
			number->fullnum[i + 1] = number->fullnum[i];
			i++;
		}
		number->fullnum[0] = retenue + '0';
		number->comapos++;
		number->fullnumbuffer++;
	}
	return (1);
}

int				float_rounding_tilcoma(int *retenue, int *i, t_bigint *number)
{
	while (*retenue != 0 && *i != number->comapos)
	{
		number->fullnum[*i] += *retenue;
		*retenue = (number->fullnum[*i] <= '9') ? 0 : 1;
		number->fullnum[*i] = (*retenue) ? number->fullnum[*i] - 10
			: number->fullnum[*i];
		(*i)--;
	}
	return (1);
}

int				float_rounding(t_bigint *number, int *prec)
{
	int			numberofdeci;
	int			i;
	int			retenue;

	numberofdeci = number->fullnumbuffer - 1 - number->comapos;
	retenue = 0;
	if (*prec < 0)
		*prec = 6;
	if ((*prec) + 1 > numberofdeci
			|| number->fullnum[number->comapos + *prec + 1] < '5')
		return (0);
	else if (number->fullnum[number->comapos + *prec + 1] > '5')
		retenue = 1;
	else if (number->fullnum[number->comapos + *prec + 1] == '5'
			&& mustround(number, *prec, numberofdeci))
		retenue = 1;
	i = number->comapos + *prec;
	float_rounding_tilcoma(&retenue, &i, number);
	if (retenue == 1 && i == number->comapos)
		float_rounding_pastcoma(retenue, i, number);
	return (1);
}

int				buff_fillfloatdeci(t_splitd *num, t_bigint *number, t_penv *env,
		t_arg *arg)
{
	fill_bigint(number, num);
	float_rounding(number, &(arg->prec));
	float_writeoutput(number, num, env, arg);
	return (1);
}
