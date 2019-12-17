/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:42:29 by toliver           #+#    #+#             */
/*   Updated: 2017/11/08 15:28:34 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void				ft_strclr(char *s)
{
	unsigned int	i;

	i = -1;
	if (s)
		while (s[++i])
			s[i] = '\0';
}