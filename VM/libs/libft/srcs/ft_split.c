/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 19:48:24 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 05:21:41 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		is_charset(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

static int		wordnumber(char *str, char *charset, int *words, int *size)
{
	if (!str || !charset)
	{
		*words = !str ? 0 : 1;
		*size = str ? ft_strlen(str) + 1 : 0;
		return (1);
	}
	while (*str)
	{
		if (!is_charset(*str, charset))
		{
			(*words)++;
			while (!is_charset(*str, charset) && *str)
			{
				str++;
				(*size)++;
			}
		}
		else
		{
			while (is_charset(*str, charset))
				str++;
		}
	}
	*size += *words;
	return (1);
}

static int		fill_string(char *arrstr, char *str, int *c, char *charset)
{
	int	i;

	i = 0;
	while (*str && !is_charset(*str, charset))
	{
		arrstr[i] = *str;
		i++;
		str++;
		(*c)++;
	}
	arrstr[i] = '\0';
	(*c)++;
	return (i);
}

static int		fill_array(char ***arr, int words, char *str, char *charset)
{
	int		word;
	int		c;

	word = 0;
	c = 0;
	while (*str)
	{
		if (!is_charset(*str, charset))
		{
			(*arr)[word] = ((char*)&((*arr)[words + 1])) + c;
			str += fill_string((*arr)[word], str, &c, charset);
			word++;
		}
		while (is_charset(*str, charset))
			str++;
	}
	return (1);
}

char			**ft_split(char *str, char *charset)
{
	int			words;
	int			size;
	char		**arr;

	words = 0;
	size = 0;
	arr = NULL;
	wordnumber(str, charset, &words, &size);
	if (!(arr = (char**)malloc(sizeof(char*) * (words + 1)
					+ sizeof(char) * (size))))
		return (NULL);
	arr[words] = NULL;
	if (!str)
		return (arr);
	if (!charset)
	{
		arr[0] = (char*)&(arr[2]);
		ft_strcpy(arr[0], str);
		return (arr);
	}
	fill_array(&arr, words, str, charset);
	return (arr);
}
