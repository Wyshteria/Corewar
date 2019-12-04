/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:58:28 by toliver           #+#    #+#             */
/*   Updated: 2019/01/09 17:36:16 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strnew(size_t size)
{
	char			*str;
	unsigned int	i;

	i = -1;
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (++i <= size)
		str[i] = '\0';
	return (str);
}
