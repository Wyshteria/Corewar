/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 19:33:14 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:34 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				parse_apostropheflag(t_penv *env, t_arg *arg)
{
	env->str++;
	arg->flags |= 1;
	return (1);
}

void			flags_cleanup(t_arg *arg)
{
	if ((arg->flags & 8) && arg->prec != -1 && arg->cat >= 0 && arg->cat != 2
			&& arg->cat != 3 && !(arg->cat == 1))
		arg->flags ^= 8;
	if ((arg->flags & 32) && (arg->flags & 8))
		arg->flags ^= 8;
	if ((arg->flags & 16) && arg->flags & 4)
		arg->flags ^= 4;
	if ((arg->type == 10 || arg->type == 11) && arg->prec < 0)
		arg->prec = 6;
	if (arg->flags & 1 && !(arg->type == 11 || arg->type == 1 || arg->type == 3
				|| arg->type == 12))
		arg->flags ^= 1;
}
