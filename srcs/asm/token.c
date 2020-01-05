/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboukrou <lboukrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:55:24 by toliver           #+#    #+#             */
/*   Updated: 2020/01/05 02:39:10 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_parse_unknown(t_file *file)
{
	t_token	token;
	char	separator[4];

	separator[0] = NEWLINE_CHAR;
	separator[1] = ' ';
	separator[2] = SEPARATOR_CHAR;
	separator[3] = '\0';
	ft_token_init(&token, UNKNOWN, file->col, file->line);
	ft_parse_until(file, separator, &(token.value), 1);
	ft_add_token(file, &token);
	ft_syntax_error(file, ft_last_token(file));
}

static void	ft_check_direct_token(t_file *file)
{
	t_token	*const last = ft_last_token(file);

	if (last && last->prev && last->prev->type == DIRECT && !last->prev->value)
	{
		ft_printf("Direct has problem\n");
		ft_lexical_error(file, last->prev);
	}
}

static int	ft_parse_token2(t_env *env, t_file *file, char *buf)
{
	if ((buf[0] == COMMENT_CHAR || buf[0] == ALT_COMMENT_CHAR) &&
			ft_offset_head(env, file, 1) && (file->col += 1))
		ft_parse_comment(file);
	else if (buf[0] == CMD_CHAR && ft_offset_head(env, file, 1))
		ft_parse_cmd(file);
	else if (buf[0] == STRING_CHAR && ft_offset_head(env, file, 1))
		ft_parse_string(file);
	else if (buf[0] == LABEL_CHAR && ft_offset_head(env, file, 1)
			&& (file->col += 1))
		ft_parse_indirect_label(file);
	else if (buf[0] == DIRECT_CHAR && ft_offset_head(env, file, 1))
		ft_parse_direct(file);
	else if (buf[0] == NEWLINE_CHAR && ft_offset_head(env, file, 1))
		ft_parse_newline(file);
	else if (buf[0] == SEPARATOR_CHAR && ft_offset_head(env, file, 1))
		ft_parse_separator(file);
	else if (buf[0] == '-' && ft_offset_head(env, file, 0))
		ft_parse_indirect(file);
	else if (ft_is_one_of(buf[0], LABEL_CHARS)
			&& ft_offset_head(env, file, 0))
		ft_parse_instruction(file);
	else
		return (0);
	return (1);
}

void		ft_parse_token(t_env *env, t_file *file)
{
	char	buf[51];
	int		retval;

	if ((retval = read(file->fd, buf, 50)) > 0)
	{
		buf[retval] = 0;
		// ft_printf("nous sommes at [%d:%d]\n", file->line, file->col);
		if (ft_parse_token2(env, file, buf))
			;
		else
		{
			ft_offset_head(env, file, 0);
			ft_parse_unknown(file);
		}
		if (file->mode == PARSING || file->mode == DONE)
			ft_check_direct_token(file);
			// ft_printf("End at [%d:%d]\n", file->line, file->col);
	}
	else if (retval == -1)
		ft_error(env, file, READ_ERROR);
	else if (retval == 0)
		file->mode = DONE;
}
