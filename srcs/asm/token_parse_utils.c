/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboukrou <lboukrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 21:16:36 by lboukrou          #+#    #+#             */
/*   Updated: 2020/01/04 21:30:46 by lboukrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_parse_comment(t_file *file)
{
	char	*comment;

	comment = NULL;
	ft_parse_until(file, (char[]){NEWLINE_CHAR, '\0'}, &comment, 0);
	free(comment);
}

void		ft_parse_cmd(t_file *file)
{
	t_token	token;

	ft_token_init(&token, COMMAND, file->col, file->line);
	ft_offset_lines(ft_get_env(), file, (char[]){CMD_CHAR, '\0'});
	ft_parse_while(file, LABEL_CHARS, &(token.value));
	ft_add_token(file, &token);
}

void		ft_parse_string(t_file *file)
{
	t_token		token;

	ft_token_init(&token, STRING, file->col, file->line);
	ft_offset_lines(ft_get_env(), file, ((char[]){STRING_CHAR, '\0'}));
	ft_parse_until(file, (char[]){STRING_CHAR, '\0'}, &(token.value), 1);
	ft_add_token(file, &token);
	//check what happens if string_char not terminated
}

void		ft_parse_newline(t_file *file)
{
	t_token	token;
	char	separator[2];

	separator[0] = NEWLINE_CHAR;
	separator[1] = '\0';
	ft_token_init(&token, NEWLINE, file->col, file->line);
	if (!(token.value = ft_strdup(separator)))
		ft_crash(MALLOC_FAIL);
	ft_add_token(file, &token);
	file->line += 1;
	file->col = 1;
}

void		ft_parse_separator(t_file *file)
{
	t_token	token;
	char	separator[2];

	separator[0] = SEPARATOR_CHAR;
	separator[1] = '\0';
	ft_token_init(&token, SEPARATOR, file->col, file->line);
	if (!(token.value = ft_strdup(separator)))
		ft_crash(MALLOC_FAIL);
	ft_add_token(file, &token);
	file->col += 1;
}
