/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:15:57 by toliver           #+#    #+#             */
/*   Updated: 2017/11/08 03:20:16 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
	{
		*((char*)(dst + i)) = *((char*)(src + i));
		if (*((unsigned char*)(src + i)) == (unsigned char)c)
			return ((char*)(dst + i + 1));
	}
	return (NULL);
}
