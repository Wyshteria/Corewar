/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:55:24 by toliver           #+#    #+#             */
/*   Updated: 2019/12/10 18:26:58 by toliver          ###   ########.fr       */
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
	}
}

void		ft_token_init(t_token *token, int type, int col, int line)
{
	token->type = type;
	token->col = col;
	token->line = line;
	token->int_value = 0;
	token->next = NULL;
	token->value = NULL;
}

void		ft_parse_comment(t_file *file)
{
	t_token	token;

	ft_token_init(&token, COMMENT, file->col, file->line);
	ft_parse_until(file, "\n", &(token.value), 0);
	ft_add_token(file, &token);
}

void		ft_parse_cmd(t_file *file)
{
	t_token	token;

	ft_token_init(&token, COMMAND, file->col, file->line);
	ft_parse_while(file, LABEL_CHARS, &(token.value));
	ft_add_token(file, &token);
}

void		ft_parse_string(t_file *file)
{
	// PENSER A VERIFIER SI LA STRING NE FINIT JAMAIS !
	t_token	token;
	
	ft_token_init(&token, STRING, file->col, file->line);
	ft_parse_until(file, "\"", &(token.value), 1);
	// ici verifier le retour ou un truc pour si la string finit jamais
	ft_add_token(file, &token);
}

void		ft_parse_label(t_file *file)
{
	t_token	token;

	ft_token_init(&token, LABEL, file->col, file->line);
	ft_parse_while(file, LABEL_CHARS, &(token.value));
	ft_add_token(file, &token);
}

void		ft_parse_direct(t_file *file)
{
	t_token	token;

	ft_token_init(&token, DIRECT, file->col, file->line);
	if (!(token.value = ft_strdup("%")))
		ft_crash(MALLOC_FAIL);
	ft_add_token(file, &token);
}

void		ft_parse_newline(t_file *file)
{
	t_token	token;

	ft_token_init(&token, NEWLINE, file->col, file->line);
	if (!(token.value = ft_strdup("\n")))
		ft_crash(MALLOC_FAIL);
	ft_add_token(file, &token);
	file->line += 1;
	file->col = 0;
}

void		ft_parse_separator(t_file *file)
{
	t_token	token;

	ft_token_init(&token, SEPARATOR, file->col, file->line);
	if (!(token.value = ft_strdup(",")))
		ft_crash(MALLOC_FAIL);
	ft_add_token(file, &token);
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
	if (i != 0 && token->value[i] == '\0')
	{
		token->int_value = ft_atoi(token->value);
		return (1);
	}	
	// verifier qu'on a bien la bonne valeur en int
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

void		ft_parse_label_op_reg(t_file *file)
{
	t_token	token;

	ft_token_init(&token, LABEL, file->col, file->line);
	ft_parse_while(file, LABEL_CHARS, &(token.value));
	token.type = ft_label_or_op(file, &token); // penser a parser si c'est des registres ou unknown 
	ft_add_token(file, &token);
	// trouver comment faire la diff entre un label et une op
}

void		ft_parse_unknown(t_file *file)
{
	t_token	token;

	ft_token_init(&token, NUMBER, file->col, file->line);
	ft_parse_until(file, "\n ,", &(token.value), 1);
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
		else if (buf[0] == NEWLINE_CHAR && ft_offset_head(env, file, 1))
			ft_parse_newline(file);
		else if (buf[0] == SEPARATOR_CHAR && ft_offset_head(env, file, 1))
			ft_parse_separator(file);
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
