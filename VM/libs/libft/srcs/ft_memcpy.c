/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:19:41 by toliver           #+#    #+#             */
/*   Updated: 2017/11/08 02:57:52 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	if (len == 0)
		return (dst);
	while (--len > 0)
		*((char*)(dst + len)) = *((char*)(src + len));
	*((char*)(dst + len)) = *((char*)(src + len));
	return (dst);
}
