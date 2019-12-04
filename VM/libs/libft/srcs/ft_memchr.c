/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:17:28 by toliver           #+#    #+#             */
/*   Updated: 2017/11/08 16:04:29 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && *((unsigned char*)(b + i)) != (unsigned char)c)
		i++;
	if (i < len && *(unsigned char*)(b + i) == (unsigned char)c)
		return ((unsigned char*)(b + i));
	return (NULL);
}
