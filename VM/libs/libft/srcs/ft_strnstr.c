/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:58:59 by toliver           #+#    #+#             */
/*   Updated: 2017/11/07 11:59:33 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (little[0] == '\0')
		return ((char*)big);
	while (*big && len)
	{
		if (*big == *little)
		{
			i = 0;
			while (big[i] == little[i] && little[i] && big[i] && len - i > 0)
				i++;
			if (little[i] == '\0')
				return ((char*)big);
		}
		big++;
		len--;
	}
	return (NULL);
}
