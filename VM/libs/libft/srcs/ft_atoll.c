/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:07:15 by toliver           #+#    #+#             */
/*   Updated: 2018/11/22 23:09:37 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long int				ft_atoll(const char *str)
{
	unsigned long long int	result;
	int						sign;

	result = 0;
	sign = 1;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			sign = -1;
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return ((long long int)result * sign);
}
