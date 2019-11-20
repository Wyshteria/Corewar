/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 12:02:06 by toliver           #+#    #+#             */
/*   Updated: 2017/11/07 12:02:48 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *big, const char *little)
{
	size_t	i;

	if (little[0] == '\0')
		return ((char*)big);
	while (*big)
	{
		if (*big == *little)
		{
			i = 0;
			while (big[i] == little[i] && little[i] && big[i])
				i++;
			if (little[i] == '\0')
				return ((char*)big);
		}
		big++;
	}
	return (NULL);
}
