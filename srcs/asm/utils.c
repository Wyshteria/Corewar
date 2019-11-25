/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 21:55:29 by toliver           #+#    #+#             */
/*   Updated: 2019/11/25 22:00:35 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		*ft_malloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
		ft_crash(MALLOC_FAIL);
	return (ptr);
}

int			ft_pow2(int pow)
{
	int		i;
	int		value;

	if (pow < 0)
		return (0);
	value = 1;
	i = 0;
	while (i < pow)
	{
		value *= 2;
		i++;
	}
	return (value);
}

int			ft_strchr_pos(char *str, int c)
{
	char	*val;

	val = ft_strchr(str, c);
	if (val == NULL)
		return (-1);
	return ((int)(val - str));
}
