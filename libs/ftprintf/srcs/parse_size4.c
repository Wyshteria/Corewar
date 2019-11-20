/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_size4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 21:50:05 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:43 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				parse_esize(t_penv *env, t_arg *arg)
{
	arg->cat = 1;
	arg->type = 10;
	arg->length = (arg->length >= 8) ? 8 : 0;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_fillfloat(env, arg);
	env->str++;
	return (0);
}

int				parse_fsize(t_penv *env, t_arg *arg)
{
	arg->cat = 1;
	arg->type = 11;
	arg->length = (arg->length >= 8) ? 8 : 0;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_fillfloat(env, arg);
	env->str++;
	return (0);
}

int				parse_gsize(t_penv *env, t_arg *arg)
{
	arg->cat = 1;
	arg->type = 12;
	arg->length = (arg->length >= 8) ? 8 : 0;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	env->str++;
	return (0);
}

int				parse_asize(t_penv *env, t_arg *arg)
{
	arg->cat = 1;
	arg->type = 13;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_fillfloat(env, arg);
	env->str++;
	return (0);
}

int				parse_bsize(t_penv *env, t_arg *arg)
{
	arg->cat = 4;
	arg->type = 14;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_fillbinary(env, arg);
	env->str++;
	return (0);
}
