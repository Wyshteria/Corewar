/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:25:31 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:35 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void			fill_buffer(t_penv *env, char c, int i)
{
	while (i > 0)
	{
		env->buff[env->buffi] = c;
		i--;
		env->buffi++;
		buff_check(env);
	}
}

int				parse_pcsize(t_penv *env, t_arg *arg)
{
	env->str++;
	arg->cat = -1;
	flags_cleanup(arg);
	if (arg->width > 1 && !(arg->flags & 32))
		fill_buffer(env, (arg->flags & 8) ? '0' : ' ', arg->width - 1);
	env->buff[env->buffi] = '%';
	env->buffi++;
	if (arg->flags & 32)
		fill_buffer(env, ' ', arg->width - 1);
	return (0);
}
