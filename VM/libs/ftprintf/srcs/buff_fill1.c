/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fill1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 03:27:05 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			buff_fills(t_penv *env, t_arg *arg)
{
	int		i;

	i = -1;
	if (arg->argument.cptr == NULL || arg->argument.wcptr == NULL)
	{
		arg->argument.cptr = env->null;
		arg->length = 0;
	}
	if (arg->length != 0)
		return (buff_fillwstr(env, arg));
	if (!(arg->flags & 32) && chartofill(arg, 0))
		buff_padding(env, arg, chartofill(arg, 0));
	while (arg->argument.cptr[++i] && ((arg->prec == -1) || i < arg->prec))
		buff_fillwith(env, arg->argument.cptr[i]);
	if ((arg->flags & 32) && chartofill(arg, 0))
		buff_padding(env, arg, chartofill(arg, 0));
	return (1);
}

int			buff_fillwstrnull(t_penv *env, t_arg *arg)
{
	arg->argument.cptr = NULL;
	arg->length = 0;
	return (buff_fills(env, arg));
}

int			buff_fillwstr(t_penv *env, t_arg *arg)
{
	size_t	i;
	size_t	charnbr;
	wint_t	wch;

	if (arg->argument.wcptr == NULL)
		return (buff_fillwstrnull(env, arg));
	i = 0;
	charnbr = ft_wcharstrlen(env, arg);
	if (!(arg->flags & 32) && arg->width > 0)
		buff_padding(env, arg, arg->width);
	while (arg->argument.wcptr[i] && arg->prec < 0 && i < charnbr)
	{
		wch = arg->argument.wcptr[i];
		if ((wch >= 0xD800 && wch <= 0xDFFF) || (wch > 0xff && MB_CUR_MAX == 1))
			return (-1);
		else if (wch <= 127 || (wch <= 0xff && MB_CUR_MAX == 1))
			buff_fillwith(env, wch);
		else
			buff_putwchar(env, arg->argument.wcptr[i]);
		i++;
	}
	if ((arg->flags & 32) && arg->width > 0)
		buff_padding(env, arg, arg->width);
	return (1);
}
