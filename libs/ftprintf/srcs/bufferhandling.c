/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferhandling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 20:41:34 by toliver           #+#    #+#             */
/*   Updated: 2020/02/27 02:51:40 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#include <stdio.h>

void			buff_check(t_penv *env)
{
	if (env->buffi == BUFFSIZE)
	{
		env->buffilasttoken = env->buffi;
		buff_flush(env);
	}
}

void			buff_malloc(t_penv *env, int len)
{
	int			i;

	env->printfstr = (char*)malloc(sizeof(char) * (len + 1));
	if (env->printfstr == NULL)
		return ;
	i = 0;
	while (i < len)
	{
		env->printfstr[i] = env->buff[i];
		i++;
	}
	env->printfstr[i] = '\0';
}

void			buff_flush(t_penv *env)
{
	int	unused;

	env->printflen += env->buffilasttoken;
	if (env->is_whatprintf == 0)
		unused = write(1, env->buff, env->buffilasttoken);
	else if (env->is_whatprintf == 1)
		buff_malloc(env, env->printflen);
	else if (env->is_whatprintf == 2)
		unused = write(env->fd, env->buff, env->buffilasttoken);
	env->buffi = 0;
	env->buffilasttoken = 0;
	(void)unused;
}
