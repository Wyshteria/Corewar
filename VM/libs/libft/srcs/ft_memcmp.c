/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:18:12 by toliver           #+#    #+#             */
/*   Updated: 2017/11/08 05:55:34 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_memcmp(const void *b1, const void *b2, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0)
		return (0);
	while ((i < len) && (((unsigned char*)b1)[i] == ((unsigned char*)b2)[i]))
		i++;
	if (i != len)
		return (((unsigned char*)b1)[i] - ((unsigned char*)b2)[i]);
	else
		return (0);
}
