/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_size2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 21:48:54 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:40 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				parse_bigosize(t_penv *env, t_arg *arg)
{
	arg->cat = 0;
	arg->type = 2;
	arg->length = (arg->length < 3) ? 3 : arg->length;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_filloct(env, arg);
	env->str++;
	return (0);
}

int				parse_usize(t_penv *env, t_arg *arg)
{
	arg->cat = 0;
	arg->type = 3;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_filluint(env, arg);
	env->str++;
	return (0);
}

int				parse_bigusize(t_penv *env, t_arg *arg)
{
	arg->cat = 0;
	arg->type = 3;
	arg->length = (arg->length < 3) ? 3 : arg->length;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_filluint(env, arg);
	env->str++;
	return (0);
}

int				parse_xsize(t_penv *env, t_arg *arg)
{
	arg->cat = 0;
	arg->type = 4;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_fillhexa(env, arg);
	env->str++;
	return (0);
}

int				parse_bigxsize(t_penv *env, t_arg *arg)
{
	arg->cat = 0;
	arg->type = 5;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_fillhexa(env, arg);
	env->str++;
	return (0);
}
