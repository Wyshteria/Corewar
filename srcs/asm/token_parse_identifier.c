/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse_identifier.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboukrou <lboukrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 21:33:41 by lboukrou          #+#    #+#             */
/*   Updated: 2020/01/04 21:34:22 by lboukrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_is_number(t_token *token)
{
	int		i;

	i = 0;
	if (token->value && token->value[0] == '-')
		i++;
	while (token->value && token->value[i])
	{
		if (token->value[i] < '0' || token->value[i] > '9')
			return (0);
		i++;
	}
	if (i != 0 && i < 12 && token->value[i] == '\0')
	{
		token->int_value = ft_atoi(token->value);
		return (1);
	}
	// verifier qu'on a bien la bonne valeur en int (int max pas plus de 12 char)
	return (0);
}

int			ft_is_label(t_file *file)
{
	char	buf[1];
	int		retval;

	retval = read(file->fd, buf, 1);
	if (retval == -1)
		ft_error(ft_get_env(), file, READ_ERROR);
	else if (buf[0] == LABEL_CHAR)
	{
		ft_offset_head(ft_get_env(), file, 1);
		return (1);
	}
	else
		ft_offset_head(ft_get_env(), file, 0);
	return (0);
}

int			ft_is_reg(char *str)
{
	int		i;

	if (str[0] == 'r')
	{
		i = 1;
		while (str[i])
		{
			if (str[i] < '0' || str[i] > '9')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
