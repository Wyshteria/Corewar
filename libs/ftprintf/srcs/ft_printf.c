/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:32:16 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:40:13 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void							env_pinit(t_penv *env, const char *str)
{
	env->str = str;
	env->strcopy = str;
	env->buffilasttoken = 0;
	env->buffi = 0;
	env->lastparam = 0;
	env->printflen = 0;
	env_ptrarrayinit(env);
	env_getarrayinit(env);
	env->null[0] = '(';
	env->null[1] = 'n';
	env->null[2] = 'u';
	env->null[3] = 'l';
	env->null[4] = 'l';
	env->null[5] = ')';
	env->null[6] = '\0';
}

int								ft_dprintf(int fd, const char *str, ...)
{
	t_penv						env;

	if (str == NULL)
		return (-1);
	env_pinit(&env, str);
	env.is_whatprintf = 2;
	env.fd = fd;
	va_start(env.arg, str);
	if (parse_string(&env) == -1)
		buff_flush(&env);
	else
		buff_flush(&env);
	return (env.printflen);
}

char							*ft_sprintf(const char *str, ...)
{
	t_penv						env;

	if (str == NULL)
		return (NULL);
	env_pinit(&env, str);
	env.is_whatprintf = 1;
	va_start(env.arg, str);
	if (parse_string(&env) == -1)
		buff_flush(&env);
	else
		buff_flush(&env);
	return (env.printfstr);
}

int								ft_printf(const char *str, ...)
{
	t_penv						env;

	if (str == NULL)
	{
		write(1, "Gare au segfault !\n", 35);
		return (-1);
	}
	env_pinit(&env, str);
	env.is_whatprintf = 0;
	va_start(env.arg, str);
	if (parse_string(&env) == -1)
	{
		buff_flush(&env);
		return (-1);
	}
	buff_flush(&env);
	return (env.printflen);
}
