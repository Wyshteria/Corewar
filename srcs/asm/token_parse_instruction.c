/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse_instruction.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboukrou <lboukrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:55:24 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 21:23:19 by lboukrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		ft_parse_instruction_set_token(t_token *token,
										int ret, t_file *file)
{
	if ((*token).value[0] == 'r')
	{
		(*token).type = REGISTER;
		if ((ret = ft_strspn(&((*token).value[1]), "0123456789")) > 2)
			ret = 2;
		ft_parse_register(file, &(*token), ret + 1);
	}
	else if (ft_fetch_op((*token).value))
		(*token).type = OPERATION;
	return (1);
}

static void		ft_parse_instruction2(t_file *file, t_token *token, size_t ret)
{
	char			*line;
	const int		diff = ft_strlen(token->value) - ret;

	line = token->value;
	if (diff)
		if (!(token->value = ft_strsub(line, 0, ret)))
			ft_crash(MALLOC_FAIL);
	token->int_value = ft_atoi(token->value);
	file->col = token->col;
	file->line = token->line;
	ft_offset_lines(ft_get_env(), file, token->value);
	if (diff)
	{
		ft_add_token(file, token);
		ft_token_init(token, UNKNOWN, file->col, file->line);
		if (!(token->value = ft_strsub(line, ret, ft_strlen(line))))
			ft_crash(MALLOC_FAIL);
		free(line);
	}
}

void			ft_parse_instruction(t_file *file)
{
	t_token			token;
	int				ret;
	t_token *const	last = ft_last_token(file);

	ret = 0;
	ft_token_init(&token, UNKNOWN, file->col, file->line);
	ft_parse_while(file, LABEL_CHARS, &(token.value));
	if (ft_is_label(file) && (file->col++))
		token.type = LABEL;
	else if (ft_is_one_of(token.value[0], "0123456789"))
	{
		if ((ret = ft_strspn(token.value, "0123456789")) > 11)
			ret = 11;
		token.type = INDIRECT;
		if (last && last->type == DIRECT && !last->value)
		{
			ft_parse_instruction_direct(file, &token, last, ret);
			return ;
		}
		else
			ft_parse_instruction2(file, &token, ret);
	}
	else if (token.value[0] == 'r' || ft_fetch_op(token.value))
		ft_parse_instruction_set_token(&token, ret, file);
	ft_add_token(file, &token);
}

void			ft_parse_instruction_direct(t_file *file, t_token *token,
										t_token *last, size_t ret)
{
	char		*line;
	const int	diff = ft_strlen(token->value) - ret;

	last->value = token->value;
	line = token->value;
	if (diff)
		if (!(last->value = ft_strsub(line, 0, ret)))
			ft_crash(MALLOC_FAIL);
	last->int_value = ft_atoi(last->value);
	file->col = token->col;
	file->line = token->line;
	ft_offset_lines(ft_get_env(), file, last->value);
	if (diff)
	{
		ft_token_init(token, UNKNOWN, file->col, file->line);
		if (!(token->value = ft_strsub(line, ret, ft_strlen(line))))
			ft_crash(MALLOC_FAIL);
		free(line);
		ft_add_token(file, token);
	}
}
