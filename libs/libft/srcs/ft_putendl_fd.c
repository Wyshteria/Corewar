/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:31:55 by toliver           #+#    #+#             */
/*   Updated: 2020/02/27 02:29:26 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putendl_fd(char const *s, int fd)
{
	int		unused;

	if (s)
	{
		unused = write(fd, s, ft_strlen(s));
		unused = write(fd, "\n", 1);
	}
	(void)unused;
}
