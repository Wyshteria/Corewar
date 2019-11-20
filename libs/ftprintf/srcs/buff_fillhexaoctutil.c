/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillhexaoctutil.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:08:58 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			buff_uimaxtoahexa(t_penv *env, uintmax_t value)
{
	uintmax_t		val;

	if (value / 16)
		buff_uimaxtoahexa(env, value / 16);
	val = value % 16;
	if (val < 10)
		buff_fillwith(env, val + '0');
	else
		buff_fillwith(env, val - 10
				+ ((*env->str == 'x' || *env->str == 'p') ? 'a' : 'A'));
	return (1);
}

int			buff_uimaxtoaoct(t_penv *env, uintmax_t value)
{
	if (value / 8)
	{
		buff_uimaxtoaoct(env, value / 8);
		buff_fillwith(env, value % 8 + '0');
	}
	else
		buff_fillwith(env, value + '0');
	return (1);
}
