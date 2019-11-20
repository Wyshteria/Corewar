/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 16:12:27 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t		ft_uintmaxtlenbase(uintmax_t value, int base)
{
	size_t	i;

	i = 1;
	while (value / base > 0)
	{
		value = value / base;
		i++;
	}
	return (i);
}

size_t		ft_intmaxtlenbase(intmax_t value, int base)
{
	if (value < 0)
		return (ft_uintmaxtlenbase((uintmax_t)-value, base));
	else
		return (ft_uintmaxtlenbase((uintmax_t)value, base));
}

int			buff_uimaxtoa(t_penv *env, uintmax_t value)
{
	if (value >= 10)
	{
		buff_uimaxtoa(env, value / 10);
		buff_fillwith(env, value % 10 + '0');
	}
	else
		buff_fillwith(env, value + '0');
	return (1);
}

int			buff_imaxtoa(t_penv *env, intmax_t value)
{
	if (value < 0)
		return (buff_uimaxtoa(env, -value));
	else
		return (buff_uimaxtoa(env, value));
}
