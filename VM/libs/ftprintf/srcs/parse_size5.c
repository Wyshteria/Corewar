/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_size5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 21:51:27 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:49 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				parse_psize(t_penv *env, t_arg *arg)
{
	arg->cat = 3;
	arg->type = 9;
	arg->length = 0;
	flags_cleanup(arg);
	get_arg(env, arg);
	arg_parse(env, arg);
	buff_fillptr(env, arg);
	env->str++;
	return (0);
}
