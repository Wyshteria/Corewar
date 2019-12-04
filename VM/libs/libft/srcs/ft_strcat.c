/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:40:05 by toliver           #+#    #+#             */
/*   Updated: 2017/11/07 23:25:23 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcat(char *s, const char *append)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	while (s[++i])
		;
	while (append[++j])
		s[i + j] = append[j];
	s[i + j] = '\0';
	return (s);
}
