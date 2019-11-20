/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_size3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 21:49:29 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:41 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				parse_csize(t_penv *env, t_arg *arg)
{
	arg->cat = 2;
	arg->type = 6;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	if (buff_fillchar(env, arg) < 0)
		return (-1);
	env->str++;
	return (0);
}

int				parse_bigcsize(t_penv *env, t_arg *arg)
{
	arg->cat = 2;
	arg->type = 6;
	arg->length = (arg->length == 1) ? 3 : 0;
	arg->length = (arg->length == 0 || arg->length == 3) ? 3 : 0;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	if (buff_fillchar(env, arg) < 0)
		return (-1);
	env->str++;
	return (0);
}

int				parse_ssize(t_penv *env, t_arg *arg)
{
	arg->cat = 3;
	arg->type = 7;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	if (buff_fills(env, arg) == -1)
	{
		env->buffilasttoken = 0;
		env->printflen = 0;
		return (-1);
	}
	env->str++;
	return (0);
}

int				parse_bigssize(t_penv *env, t_arg *arg)
{
	arg->cat = 3;
	arg->type = 7;
	arg->length = (arg->length == 1) ? 3 : 0;
	arg->length = (arg->length == 0 || arg->length == 3) ? 3 : 0;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	if (buff_fills(env, arg) == -1)
	{
		env->buffilasttoken = 0;
		env->printflen = 0;
		return (-1);
	}
	env->str++;
	return (0);
}

int				parse_nsize(t_penv *env, t_arg *arg)
{
	arg->cat = 3;
	arg->type = 8;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_fillnptr(env, arg);
	env->str++;
	return (0);
}
