/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:14:14 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:25 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				get_wintt(t_penv *env, t_arg *arg)
{
	arg->argument.wi = va_arg(env->arg, wint_t);
	return (1);
}

int				get_ptr(t_penv *env, t_arg *arg)
{
	arg->argument.vptr = va_arg(env->arg, void*);
	return (1);
}
