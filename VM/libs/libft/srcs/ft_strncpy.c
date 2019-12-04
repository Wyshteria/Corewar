/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:57:11 by toliver           #+#    #+#             */
/*   Updated: 2017/11/07 11:57:24 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	size;

	size = -1;
	while (src[++size] && size < len)
		dst[size] = src[size];
	while (size < len)
	{
		dst[size] = '\0';
		size++;
	}
	return (dst);
}
