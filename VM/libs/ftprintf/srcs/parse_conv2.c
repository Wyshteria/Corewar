/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_conv2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 20:36:33 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:28 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				parse_lmajconv(t_penv *env, t_arg *arg)
{
	env->str++;
	if (*env->str == 'L')
	{
		env->str++;
		arg->length = 9;
	}
	else
		arg->length = 8;
	return (1);
}
