/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboukrou <lboukrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 21:49:13 by lboukrou          #+#    #+#             */
/*   Updated: 2020/01/04 21:49:47 by lboukrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_add_token(t_file *file, t_token *token)
{
	t_token	*new;
	t_token	*ptr;

	if (!(new = (t_token*)malloc(sizeof(t_token))))
	{
		free(token->value);
		ft_crash(MALLOC_FAIL);
	}
	ft_memcpy(new, token, sizeof(t_token));
	if (file->tokens == NULL)
		file->tokens = new;
	else
	{
		ptr = file->tokens;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
		token->prev = ptr;
		new->prev = ptr;
	}
}

void		ft_token_init(t_token *token, int type, int col, int line)
{
	token->type = type;
	token->col = col;
	token->line = line;
	token->int_value = 0;
	token->next = NULL;
	token->prev = NULL;
	token->value = NULL;
}
