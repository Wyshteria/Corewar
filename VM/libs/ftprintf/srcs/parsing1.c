/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 16:48:59 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:32:55 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				parse_error(t_penv *env, t_arg *arg)
{
	if (*env->str)
	{
		arg->argument.uc = *env->str;
		arg->cat = 2;
		flags_cleanup(arg);
		if (buff_fillchar(env, arg) < 0)
			return (-1);
		env->str++;
	}
	return (0);
}

int				parse_preci(t_penv *env, t_arg *arg)
{
	env->str++;
	if (*env->str == '*')
	{
		arg->prec = va_arg(env->arg, int);
		if (arg->prec < 0)
			arg->prec = -1;
		env->str++;
	}
	else
	{
		arg->prec = pfatoi(env);
		if (arg->prec < 0)
			arg->prec = -1;
	}
	return (1);
}

int				parse_wildchar(t_penv *env, t_arg *arg)
{
	int			value;

	value = va_arg(env->arg, int);
	env->str++;
	if (*env->str == '$')
	{
		arg->param = value;
		env->str++;
	}
	else
	{
		arg->width = value;
		if (arg->width < 0)
		{
			arg->width = (-arg->width);
			arg->flags |= 32;
		}
	}
	return (1);
}

int				parse_number(t_penv *env, t_arg *arg)
{
	int			value;

	value = pfatoi(env);
	if (*env->str == '$')
	{
		arg->param = value;
		env->str++;
	}
	else
		arg->width = value;
	return (1);
}
