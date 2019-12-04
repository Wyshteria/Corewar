/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 20:26:29 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:50 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int					parse_string(t_penv *env)
{
	int				retval;

	while (*env->str)
	{
		if (*env->str == '%')
		{
			env->str++;
			if (*env->str)
			{
				if ((retval = parse_token(env)) == -1)
					return (-1);
				else
					env->buffilasttoken = env->buffi;
			}
		}
		else
		{
			buff_fillwith(env, *env->str);
			env->str++;
		}
	}
	env->buffilasttoken = env->buffi;
	return (1);
}

int					parse_token(t_penv *env)
{
	t_arg			arg;
	int				retval;

	arg_init(&arg);
	while ((retval = env->parse[(int)*env->str](env, &arg)) > 0)
		;
	return (retval);
}

void				arg_init(t_arg *arg)
{
	arg->param = 0;
	arg->flags = 0;
	arg->width = -1;
	arg->prec = -1;
	arg->length = 0;
	arg->type = -1;
	arg->cat = 0;
	arg->argument.i = 0;
}

int					pfatoi(t_penv *env)
{
	long long int	result;

	result = 0;
	while (*env->str >= '0' && *env->str <= '9')
	{
		result = result * 10 + *env->str - '0';
		env->str++;
		if (result > 2147483647)
		{
			while (*env->str >= '0' && *env->str <= '9')
				env->str++;
			return (-1);
		}
	}
	return ((int)result);
}
