/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jates- <jates-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 23:58:23 by toliver           #+#    #+#             */
/*   Updated: 2020/02/24 17:23:13 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

void		*ft_safe_malloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
	{
		ft_dprintf(2, "%s: Malloc failed: %s\n",
				ft_get_env()->prog_name, strerror(errno));
		ft_free_env(ft_get_env());
		exit(-1);
	}
	return (ptr);
}
