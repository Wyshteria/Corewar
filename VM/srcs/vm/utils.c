/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 23:58:23 by toliver           #+#    #+#             */
/*   Updated: 2019/12/06 06:25:50 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

uint32_t	ft_swap(uint32_t toswap)
{
	uint32_t	swapped;

	swapped = ((toswap>>24)&0xff) |
                    ((toswap<<8)&0xff0000) |
                    ((toswap>>8)&0xff00) |
                    ((toswap<<24)&0xff000000);
	return (swapped);
}

int			ft_is_containing_other_than(char *str, char *containing)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_one_of(str[i], containing))
			return (1);
		i++;
	}
	return (0);
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

int			ft_is_one_of(char c, char *lookfor)
{
	int		i;
	
	i = 0;
	while (lookfor && lookfor[i])
	{
		if (lookfor[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void		*ft_malloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
	{
		ft_dprintf(2, "%s: Malloc failed: %s\n", ft_get_env()->prog_name, strerror(errno));
		ft_free_env(ft_get_env());
		exit(-1);
	}
	return (ptr);
}
