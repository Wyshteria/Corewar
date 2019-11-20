/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:13:14 by toliver           #+#    #+#             */
/*   Updated: 2017/11/08 05:58:50 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			nbr_size(int n)
{
	int				nbrsize;
	unsigned int	nb;

	nb = n;
	nbrsize = 1;
	if (n < 0)
	{
		nbrsize++;
		nb = (unsigned)-n;
	}
	while (nb > 9)
	{
		nb /= 10;
		nbrsize++;
	}
	return (nbrsize);
}

char				*ft_itoa(int n)
{
	char			*str;
	int				nbrsize;
	unsigned int	nbr;

	nbrsize = nbr_size(n);
	nbr = n;
	if (!(str = (char*)malloc(sizeof(char) * (nbrsize + 1))))
		return (NULL);
	str[nbrsize] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		nbr = (unsigned)-n;
	}
	while (nbr != 0)
	{
		str[nbrsize - 1] = nbr % 10 + '0';
		nbr /= 10;
		nbrsize--;
	}
	return (str);
}
