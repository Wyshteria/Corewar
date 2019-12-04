/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_fill_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 16:08:29 by toliver           #+#    #+#             */
/*   Updated: 2018/12/27 10:01:55 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t		ft_wstrlen(wint_t *str)
{
	int		i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

size_t		ft_pstrlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

size_t		chartofill(t_arg *arg, int wchar)
{
	size_t	strlen;

	if (!wchar)
	{
		strlen = ft_pstrlen(arg->argument.cptr);
		if (arg->prec >= 0 && (size_t)arg->prec < strlen)
			strlen = arg->prec;
		if (arg->width >= 0 && (size_t)arg->width > strlen)
			return (arg->width - strlen);
	}
	return (0);
}

size_t		ft_wcharstrlen(t_penv *env, t_arg *arg)
{
	size_t	i;
	size_t	charnbr;
	int		bytenumber;

	(void)env;
	i = 0;
	charnbr = 0;
	while (arg->argument.wcptr[i])
	{
		bytenumber = octsize(arg->argument.wcptr[i]);
		if (arg->prec >= 0 && ((int)charnbr + bytenumber) > arg->prec)
			break ;
		if (bytenumber > 0)
			charnbr += bytenumber;
		else if (bytenumber == 0
				&& arg->argument.wcptr[i] <= 0xff && MB_CUR_MAX == 1)
			charnbr += 1;
		i++;
	}
	if (arg->prec > 0)
		arg->prec = -1;
	arg->width -= charnbr;
	return (i);
}

int			issmaller(wchar_t *str, int prec)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (str[i])
	{
		size += octsize(str[i]);
		i++;
	}
	if (size <= prec)
		return (1);
	return (0);
}
