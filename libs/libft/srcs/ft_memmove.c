/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:20:41 by toliver           #+#    #+#             */
/*   Updated: 2017/11/07 11:29:31 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = -1;
	if (dst > src)
	{
		while ((int)--len >= 0)
			*((char*)(dst + len)) = *((char*)(src + len));
	}
	else
	{
		while (++i < len)
			*((char*)(dst + i)) = *((char*)(src + i));
	}
	return (dst);
}
