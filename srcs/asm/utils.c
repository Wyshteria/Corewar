/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jates- <jates-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 21:55:29 by toliver           #+#    #+#             */
/*   Updated: 2020/02/24 17:23:11 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token		*ft_last_token(t_file *file)
{
	t_token *token;

	token = file->tokens;
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

void		*ft_safe_malloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
		ft_crash(MALLOC_FAIL);
	return (ptr);
}

int			ft_pow2(int pow)
{
	int		i;
	int		value;

	if (pow < 0)
		return (0);
	value = 1;
	i = 0;
	while (i < pow)
	{
		value *= 2;
		i++;
	}
	return (value);
}

int			ft_strchr_pos(char *str, int c)
{
	char	*val;

	val = ft_strchr(str, c);
	if (val == NULL)
		return (-1);
	return ((int)(val - str));
}

int			ft_is_one_of(char c, char *lookfor)
{
	int		i;

	i = 0;
	while (lookfor && lookfor[i])
	{
		if (lookfor[i] == c)
			return (c);
		i++;
	}
	return (0);
}
