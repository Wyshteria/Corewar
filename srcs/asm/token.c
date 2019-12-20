/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:55:24 by toliver           #+#    #+#             */
/*   Updated: 2019/12/07 19:05:50 by toliver          ###   ########.fr       */
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

void		ft_parse_comment(t_file *file)
{
	char	separator[2];
	char 	*comment;
	t_token *const last = ft_last_token(file);
	
	separator[0] = NEWLINE_CHAR;
	separator[1] = '\0';
	comment = NULL;
	if (last && last->prev && last->prev->type < STRING)
	{
		ft_lexical_error(file, last);
		file->mode = CONTAIN_ERRORS;
	}
	else
		ft_parse_until(file, separator, &comment, 0);
	free(comment);
}

void		ft_parse_cmd(t_file *file)
{
	t_token	token;

	ft_token_init(&token, COMMAND, file->col, file->line);
	ft_parse_while(file, LABEL_CHARS, &(token.value));
	if (ft_strnequ(token.value, NAME_CMD_STRING,\
		ft_strlen(NAME_CMD_STRING) + 1))
		token.type = COMMAND_NAME;
	else if (ft_strnequ(token.value, COMMENT_CMD_STRING,\
		ft_strlen(COMMENT_CMD_STRING) + 1))
		token.type = COMMAND_COMMENT;
	ft_add_token(file, &token);
	if ((token.prev && token.prev->type != NEWLINE)
		|| (token.type == COMMAND_NAME && file->header.prog_name[0])
		|| (token.type == COMMAND_COMMENT && file->header.comment[0]))
	{
		ft_syntax_error(file, &token);
		file->mode = CONTAIN_ERRORS;
	}
}

void		ft_parse_string(t_file *file)
{
	t_token		token;
	char		separator[2];
	
	separator[0] = STRING_CHAR;
	separator[1] = '\0';
	ft_token_init(&token, STRING, file->col, file->line);
	ft_parse_until(file, separator, &(token.value), 1);
	ft_add_token(file, &token);
	if (token.prev && token.prev->type == COMMAND_NAME)
		ft_memccpy(file->header.prog_name, token.value, '\0',\
		PROG_NAME_LENGTH + 1);
	else if (token.prev && token.prev->type == COMMAND_COMMENT)
		ft_memccpy(file->header.comment, token.value, '\0',\
		COMMENT_LENGTH + 1);
	else if (!token.prev || token.prev->type != COMMAND)
	{
		ft_syntax_error(file, &token);
		file->mode = CONTAIN_ERRORS;
	}
}

void		ft_parse_indirect_label(t_file *file)
{
	t_token	token;
	t_token	*const last = ft_last_token(file);

	if (last && last->type == DIRECT)
	{
		ft_parse_while(file, LABEL_CHARS, &(last->value));
		last->type = DIRECT_LABEL;
	}
	else
	{
		ft_token_init(&token, INDIRECT_LABEL, file->col, file->line);
		ft_parse_while(file, LABEL_CHARS, &(token.value));
		ft_add_token(file, &token);
	}
	if (token.prev && token.prev->type < STRING)
	{
		ft_lexical_error(file, &token);
		file->mode = CONTAIN_ERRORS;
	}
}

void		ft_parse_direct(t_file *file)
{
	t_token	token;
	char	separator[2];
	
	separator[0] = DIRECT_CHAR;
	separator[1] = '\0';
	ft_token_init(&token, DIRECT, file->col, file->line);
	// if (!(token.value = ft_strdup(separator)))
	// 	ft_crash(MALLOC_FAIL); //est-ce necessaire?
	ft_add_token(file, &token);
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
	file->col = 0;
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
	if (token.prev && token.prev->type < STRING)
	{
		ft_lexical_error(file, &token);
		file->mode = CONTAIN_ERRORS;
	}
	file->col += 1;
}

int			ft_is_reg(char *str)
{
	int		i;

	if (str[0] == 'r')
	{
		i = 1;
		while(str[i])
		{
			if (str[i] < '0' || str[i] > '9')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int			ft_is_op(t_token *token)
{
	int		i;

	i = 1;
	while (i < 17)
	{
		if (!ft_strcmp(token->value, op_tab[i].opcode))
		{
			token->int_value = i;
			return (1);
		}
		i++;
	}
	return (0);
}

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

int			ft_op_reg_other(t_token *token)
{
	if (ft_is_reg(token->value))
	{
		ft_strcpy(token->value, token->value + 1);
		token->int_value = ft_atoi(token->value);
		return (REGISTER);
	}
	else if (ft_is_op(token))
		return (OPERATION);
	else if (ft_is_number(token))
		return (NUMBER);
	return (UNKNOWN); // return other
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

int			ft_label_or_op(t_file *file, t_token *token)
{
	char	buf[1];
	int		retval;

	retval = read(file->fd, buf, 1);
	if (retval == -1)
		ft_error(ft_get_env(), file, READ_ERROR);
	else if (buf[0] == LABEL_CHAR)
	{
		file->col += 1;
		ft_offset_head(ft_get_env(), file, 1);
		return (LABEL);
	}
	else
		ft_offset_head(ft_get_env(), file, 0);
	return (ft_op_reg_other(token));
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
		while(i != retval && ft_is_one_of(buf[i], "0123456789"))
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

void		ft_parse_indirect(t_file *file)
{
	t_token token;
	t_token *const last = ft_last_token(file);

	if (last && last->type == DIRECT && last->value)
		ft_parse_number(file, last);
	else
	{
		ft_token_init(&token, INDIRECT, file->col, file->line);
		ft_parse_number(file, &token);
		ft_add_token(file, &token);
	}
}

void		ft_parse_instruction(t_file *file)
{
	t_token	token;

	ft_token_init(&token, UNKNOWN, file->col, file->line);
	ft_parse_while(file, LABEL_CHARS, &(token.value));
	if (ft_is_label(file))
		token.type = LABEL;
	else
	{
		if (!(last->value[0]))
		{
			free(last->value);
			ft_parse_number(file, &(last->value), &(last->int_value));
		}
		if (!ft_is_number(last))
			ft_lexical_error(file, last);
	}
}

void		ft_parse_label_op_reg(t_file *file)
{
	t_token	token;
	t_token *const last = ft_last_token(file);

	if (last && last->type == DIRECT)
	{
		ft_parse_while(file, LABEL_CHARS, &(last->value));
		// if (ft_label_or_op(file, &token) == LABEL)
		// 	;
	}
	else
	{
		ft_token_init(&token, LABEL, file->col, file->line);
		ft_parse_while(file, LABEL_CHARS, &(token.value));
		token.type = ft_label_or_op(file, &token); // penser a parser si c'est des registres ou unknown 
		ft_add_token(file, &token);
		// trouver comment faire la diff entre un label et une op
	}
}

void		ft_parse_unknown(t_file *file)
{
	t_token	token;
	char	separator[4];
	
	separator[0] = NEWLINE_CHAR;
	separator[1] = ' ';
	separator[2] = SEPARATOR_CHAR;
	separator[3] = '\0';
	ft_token_init(&token, NUMBER, file->col, file->line);
	ft_parse_until(file, separator, &(token.value), 1);
	token.type = ft_label_or_op(file, &token);
	ft_add_token(file, &token);
}

void		ft_parse_token(t_env *env, t_file *file)
{
	char	buf[51];
	int		retval;

	(void)env;
	if ((retval = read(file->fd, buf, 50)) > 0)
	{
		buf[retval] = 0;
		if ((buf[0] == COMMENT_CHAR || buf[0] == ALT_COMMENT_CHAR) && ft_offset_head(env, file, 1) && (file->col += 1))
			ft_parse_comment(file);
		else if (buf[0] == CMD_CHAR && ft_offset_head(env, file, 1) && (file->col += 1))
			ft_parse_cmd(file);
		else if (buf[0] == STRING_CHAR && ft_offset_head(env, file, 1) && (file->col += 1))
			ft_parse_string(file);
		else if (buf[0] == LABEL_CHAR && ft_offset_head(env, file, 1) && (file->col += 1))
			ft_parse_label(file);
		else if (buf[0] == DIRECT_CHAR && ft_offset_head(env, file, 1) && (file->col += 1))
			ft_parse_direct(file);
		else if (buf[0] == NEWLINE_CHAR && ft_offset_head(env, file, 1) && (file->col += 1))
			ft_parse_newline(file);
		else if (buf[0] == SEPARATOR_CHAR && ft_offset_head(env, file, 1))
			ft_parse_separator(file);
		else if (ft_is_one_of(buf[0], "0123456789-") && ft_offset_head(env, file, 0))
			ft_parse_indirect(file);
		else if (ft_is_one_of(buf[0], LABEL_CHARS) && ft_offset_head(env, file, 0))
			ft_parse_label_op_reg(file);
		else
		{
			ft_offset_head(env, file, 0);
			ft_parse_unknown(file);
		}
	}
	else if (retval == -1)
		ft_error(env, file, READ_ERROR);
	else if (retval == 0)
		file->mode = DONE;
}
