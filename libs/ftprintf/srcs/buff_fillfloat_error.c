/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fillfloat_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 02:48:20 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int						buff_fillerror2(t_arg *arg, int i, char buffer[])
{
	buffer[i] = 0;
	arg->length = 0;
	arg->flags &= 32;
	arg->prec = i;
	return (1);
}

int						buff_fillerror(t_splitd *num, t_penv *env, t_arg *arg)
{
	char				buffer[5];
	int					i;

	i = 0;
	if (num->isinf)
	{
		if (num->sign)
			buffer[i++] = '-';
		else if ((arg->flags & 16) || (arg->flags & 4))
			buffer[i++] = ((arg->flags & 16) ? '+' : ' ');
		buffer[i++] = (num->isuppercase) ? 'I' : 'i';
		buffer[i++] = (num->isuppercase) ? 'N' : 'n';
		buffer[i++] = (num->isuppercase) ? 'F' : 'f';
	}
	else
	{
		buffer[i++] = (num->isuppercase) ? 'N' : 'n';
		buffer[i++] = (num->isuppercase) ? 'A' : 'a';
		buffer[i++] = (num->isuppercase) ? 'N' : 'n';
	}
	buff_fillerror2(arg, i, buffer);
	arg->argument.cptr = (char*)(&buffer);
	buff_fills(env, arg);
	return (1);
}
