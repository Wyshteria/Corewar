/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:35:59 by toliver           #+#    #+#             */
/*   Updated: 2020/02/27 02:24:11 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;
	int				unused;

	nb = n;
	if (n < 0)
	{
		unused = write(fd, "-", 1);
		nb = (unsigned)-n;
	}
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	nb = nb % 10 + 48;
	unused = write(fd, &nb, 1);
	(void)unused;
}
