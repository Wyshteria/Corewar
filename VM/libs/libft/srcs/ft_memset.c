/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:21:30 by toliver           #+#    #+#             */
/*   Updated: 2017/11/08 02:56:05 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memset(void *ptr, int c, size_t len)
{
	if (len == 0)
		return (ptr);
	while (--len > 0)
		*((unsigned char*)(ptr + len)) = (unsigned char)c;
	*((unsigned char*)(ptr + len)) = (unsigned char)c;
	return (ptr);
}
