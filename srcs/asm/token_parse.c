/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboukrou <lboukrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 21:43:13 by lboukrou          #+#    #+#             */
/*   Updated: 2020/01/04 21:47:20 by lboukrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_parse_indirect_label(t_file *file)
{
	t_token			token;
	t_token *const	last = ft_last_token(file);

	if (last && last->type == DIRECT)
	{
		ft_parse_while(file, LABEL_CHARS, &(last->value));
		last->type = DIRECT_LABEL;
		if (!last->value[0])
			ft_syntax_error(file, last);
	}
	else
	{
		ft_token_init(&token, INDIRECT_LABEL, file->col, file->line);
		ft_parse_while(file, LABEL_CHARS, &(token.value));
		ft_add_token(file, &token);
		if (!token.value[0])
			ft_syntax_error(file, &token);
	}
}

void		ft_parse_direct(t_file *file)
{
	t_token	token;

	ft_token_init(&token, DIRECT, file->col, file->line);
	ft_offset_lines(ft_get_env(), file, ((char[]){DIRECT_CHAR, '\0'}));
	ft_add_token(file, &token);
}

void		ft_parse_indirect(t_file *file)
{
	t_token			token;
	t_token *const	last = ft_last_token(file);

	if (last && last->type == DIRECT && !last->value)
		ft_parse_number(file, last);
	else
	{
		ft_token_init(&token, INDIRECT, file->col, file->line);
		ft_parse_number(file, &token);
		ft_add_token(file, &token);
	}
}

void		ft_parse_register(t_file *file, t_token *token, size_t ret)
{
	char			*line;
	const int		diff = ft_strlen(token->value) - ret;

	line = token->value;
	if (!(token->value = ft_strsub(line, 1, ret)))
		ft_crash(MALLOC_FAIL);
	token->int_value = ft_atoi(token->value);
	file->col = token->col;
	file->line = token->line;
	ft_offset_lines(ft_get_env(), file, token->value);
	if (diff)
	{
		ft_add_token(file, token);
		ft_token_init(token, UNKNOWN, file->col, file->line);
		if (!(token->value = ft_strsub(line, ret, diff)))
			ft_crash(MALLOC_FAIL);
	}
	free(line);
}

int			ft_parse_number(t_file *file, t_token *token)
{
	char	buf[12];
	int		i;
	int		retval;

	i = 0;
	if ((retval = read(file->fd, buf, 11)) > 0)
	{
		i = (buf[0] == '-') ? 1 : 0;
		if (!ft_is_one_of(buf[i], "0123456789"))
			return (ft_lexical_error(file, token));
		while (i != retval && ft_is_one_of(buf[i], "0123456789"))
			i++;
	}
	if (retval == -1)
		return (ft_error(ft_get_env(), file, READ_ERROR));
	if (retval == 0)
		file->mode = DONE;
	buf[i] = '\0';
	if (!(token->value = ft_strdup(buf)))
		ft_crash(MALLOC_FAIL);
	token->int_value = ft_atoi(token->value);
	ft_offset_head(ft_get_env(), file, i);
	ft_offset_lines(ft_get_env(), file, token->value);
	return (1);
}
