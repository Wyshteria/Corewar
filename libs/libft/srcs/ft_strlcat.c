/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 08:08:06 by toliver           #+#    #+#             */
/*   Updated: 2017/11/08 11:28:08 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	srcsize;

	i = 0;
	j = 0;
	srcsize = ft_strlen(src);
	while (dst[i] && (i < size))
		++i;
	if (size > 0)
		while (src[j] && (i < size - 1))
			dst[i++] = src[j++];
	if (j > 0)
	{
		dst[i] = 0;
		return (srcsize + i - j);
	}
	return (i + srcsize);
}
