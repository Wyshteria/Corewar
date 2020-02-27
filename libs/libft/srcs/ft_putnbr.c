/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:32:51 by toliver           #+#    #+#             */
/*   Updated: 2020/02/27 02:23:10 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int	nb;
	int				unused;

	nb = n;
	if (n < 0)
	{
		unused = write(1, "-", 1);
		nb = (unsigned)-n;
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	nb = nb % 10 + 48;
	unused = write(1, &nb, 1);
	(void)unused;
}
