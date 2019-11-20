/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_conv1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 20:27:36 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:26 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				parse_hconv(t_penv *env, t_arg *arg)
{
	env->str++;
	if (*env->str == 'h')
		arg->length = (arg->length > 1) ? arg->length : 1;
	else
		arg->length = (arg->length > 2) ? arg->length : 2;
	env->str += (*env->str == 'h') ? 1 : 0;
	return (1);
}

int				parse_lconv(t_penv *env, t_arg *arg)
{
	env->str++;
	if (*env->str == 'l')
		arg->length = (arg->length > 4) ? arg->length : 4;
	else
		arg->length = (arg->length > 3) ? arg->length : 3;
	env->str += (*env->str == 'l') ? 1 : 0;
	return (1);
}

int				parse_jconv(t_penv *env, t_arg *arg)
{
	env->str++;
	arg->length = (arg->length > 5) ? arg->length : 5;
	return (1);
}

int				parse_zconv(t_penv *env, t_arg *arg)
{
	env->str++;
	arg->length = (arg->length > 6) ? arg->length : 6;
	return (1);
}

int				parse_tconv(t_penv *env, t_arg *arg)
{
	env->str++;
	arg->length = 7;
	return (1);
}
