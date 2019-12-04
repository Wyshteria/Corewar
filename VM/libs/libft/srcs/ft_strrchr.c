/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:59:45 by toliver           #+#    #+#             */
/*   Updated: 2017/11/07 12:00:24 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*str;

	str = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			str = (char*)s;
		s++;
	}
	if ((char)c == '\0')
		str = (char*)s;
	return (str);
}
