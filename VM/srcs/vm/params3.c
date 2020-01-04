/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 04:17:36 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 04:24:54 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					ft_parse_int(t_env *env, char *s, int *ptr)
{
	int				i;
	int				value;
	char			*check;

	value = ft_atoi(s);
	check = ft_itoa(value);
	if (!check)
	{
		ft_dprintf(2, "%s: Malloc failed: %s\n",
				ft_get_env()->prog_name, strerror(errno));
		return (PARSING_CRASH);
	}
	i = 0;
	if (s[0] == '+')
		s++;
	while (check[i] && s[i] && check[i] == s[i])
		i++;
	if (check[i])
	{
		free(check);
		return (ft_parsing_error(env, PARSING_OVERFLOW, s, NULL));
	}
	free(check);
	*ptr = value;
	return (PARSING_RUNNING);
}

int					nbr_sizet(size_t nb)
{
	int				nbrsize;

	nbrsize = 1;
	while (nb > 9)
	{
		nb /= 10;
		nbrsize++;
	}
	return (nbrsize);
}

char				*ft_sizettoa(size_t nbr)
{
	char			*str;
	int				nbrsize;

	nbrsize = nbr_sizet(nbr);
	if (!(str = (char*)malloc(sizeof(char) * (nbrsize + 1))))
		return (NULL);
	str[nbrsize] = '\0';
	if (nbr == 0)
		str[0] = '0';
	while (nbr != 0)
	{
		str[nbrsize - 1] = nbr % 10 + '0';
		nbr /= 10;
		nbrsize--;
	}
	return (str);
}

size_t				ft_atosize_t(char *str)
{
	size_t			result;

	result = 0;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

int					ft_parse_size_t(t_env *env, char *s, size_t *ptr,
		char *flag)
{
	int				i;
	size_t			value;
	char			*check;

	if (s[0] == '-' || (s[0] == '+' && s[1] == '-'))
		return (ft_parsing_error(env, PARAM_NEGATIVE, flag, s));
	value = ft_atosize_t(s);
	check = ft_sizettoa(value);
	if (!check)
	{
		ft_dprintf(2, "%s: Malloc failed: %s\n",
			ft_get_env()->prog_name, strerror(errno));
		return (PARSING_CRASH);
	}
	i = 0;
	if (s[0] == '+')
		s++;
	while (check[i] && s[i] && check[i] == s[i])
		i++;
	free(check);
	if (s[i])
		return (ft_parsing_error(env, PARSING_OVERFLOW, s, NULL));
	*ptr = value;
	return (PARSING_RUNNING);
}
