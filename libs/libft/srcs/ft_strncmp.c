/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:56:26 by toliver           #+#    #+#             */
/*   Updated: 2017/11/08 06:34:41 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t len)
{
	while (*s1 == *s2 && s1 && *s1 && len > 0)
	{
		s1++;
		s2++;
		len--;
	}
	if ((*s1 == *s2 && *s1 == '\0') || len == 0)
		return (0);
	return (*((unsigned char*)s1) - *((unsigned char*)s2));
}
