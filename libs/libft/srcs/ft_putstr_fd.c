/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:37:59 by toliver           #+#    #+#             */
/*   Updated: 2020/02/27 02:33:40 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putstr_fd(char const *s, int fd)
{
	int	unused;

	if (s)
		unused = write(fd, s, ft_strlen(s));
	(void)unused;
}
