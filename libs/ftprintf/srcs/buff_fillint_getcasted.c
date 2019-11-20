/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillint_getcasted.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 16:25:14 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

intmax_t	get_castedintmaxt(t_arg *arg)
{
	if (arg->length == 0)
		return ((intmax_t)arg->argument.i);
	else if (arg->length == 1)
		return ((intmax_t)arg->argument.sc);
	else if (arg->length == 2)
		return ((intmax_t)arg->argument.si);
	else if (arg->length == 3)
		return ((intmax_t)arg->argument.li);
	else if (arg->length == 4)
		return ((intmax_t)arg->argument.lli);
	else if (arg->length == 5)
		return ((intmax_t)arg->argument.imax);
	else if (arg->length == 6)
		return ((intmax_t)arg->argument.siz);
	else if (arg->length == 7)
		return ((intmax_t)arg->argument.ptd);
	else
		return ((intmax_t)arg->argument.i);
}

intmax_t	get_casteduintmaxt(t_arg *arg)
{
	if (arg->length == 0)
		return ((intmax_t)arg->argument.ui);
	else if (arg->length == 1)
		return ((intmax_t)arg->argument.uc);
	else if (arg->length == 2)
		return ((intmax_t)arg->argument.usi);
	else if (arg->length == 3)
		return ((intmax_t)arg->argument.uli);
	else if (arg->length == 4)
		return ((intmax_t)arg->argument.ulli);
	else if (arg->length == 5)
		return ((intmax_t)arg->argument.uimax);
	else if (arg->length == 6)
		return ((intmax_t)arg->argument.siz);
	else if (arg->length == 7)
		return ((intmax_t)arg->argument.ptd);
	else
		return ((intmax_t)arg->argument.i);
}
