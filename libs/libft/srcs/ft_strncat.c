/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:55:26 by toliver           #+#    #+#             */
/*   Updated: 2017/11/07 21:58:52 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncat(char *s, const char *append, size_t count)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	while (s[++i])
		;
	while (append[++j] && j < count)
		s[i + j] = append[j];
	s[i + j] = '\0';
	return (s);
}
