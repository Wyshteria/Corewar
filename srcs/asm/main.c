/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:18 by toliver           #+#    #+#             */
/*   Updated: 2019/11/28 23:45:37 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_dump_file(t_file *file)
{
	ft_printf("\tfile name = %s\n", file->filename);
	ft_printf("\tfile fd = %d\n", file->fd);
	ft_printf("\tline:col [%d:%d]\n", file->line, file->col);
	ft_printf("\tfile offset = %zu\n", file->offset);
	ft_printf("\t file mode = %d\n", file->mode);
	ft_printf("\n");
}

void		ft_dump_files(t_file *files)
{
	t_file	*ptr;

	ptr = files;
	while (ptr)
	{
		ft_dump_file(ptr);
		ptr = ptr->next;
	}
}

void		ft_dump_env(t_env *env)
{
	ft_printf("prog name : %s\n", env->prog_name);
	ft_printf("prog flags = %b\n", env->flags);
	ft_dump_files(env->files);
}

int			ft_error(t_env *env, t_file *file, int error)
{
	(void)error;
	ft_dprintf(2, "%s: %s: %s\n", env->prog_name, file->filename, strerror(errno));
	file->mode = CRASH;
	return (0);
}

int			ft_open_file(t_env *env, t_file *file)
{
	int		fd;

	fd = open(file->filename, O_RDONLY);
	file->fd = fd;
	if (fd == -1)
	{
		ft_error(env, file, OPEN_ERROR); 
		return (0);
	}
	return (1);
}

void		ft_delete_file(t_env *env, t_file *file)
{
	t_file	*ptr;

	if (env->files == file)
		env->files = file->next;
	else
	{
		ptr = env->files;
		while (ptr->next != file)
			ptr = ptr->next;
		ptr->next = file->next;
	}
	ft_free_file(file);
}

int			ft_offset_head(t_env *env, t_file *file, size_t size)
{
	file->offset = lseek(file->fd, file->offset + size, SEEK_SET);
	if (file->offset == -1)
	{
		ft_error(env, file, LSEEK_ERROR);
		return (0);
	}
	return (1);
}

int			ft_offset_lines(t_env *env, t_file *file, char *str)
{
	int		i;

	i = 0;
	(void)env;
	while (str && str[i])
	{
		if (str[i] == NEWLINE_CHAR)
		{
			file->line += 1;
			file->col = 0;
		}
		else
			file->col += 1;
		i++;
	}
	return (1);
}

int			ft_is_one_of(char c, char *lookfor)
{
	int		i;
	
	i = 0;
	while (lookfor[i])
	{
		if (lookfor[i] == c)
			return (1);
		i++;
	}
	return (0);
}


void		ft_skip_spaces(t_env *env, t_file *file)
{
	int		size;
	int		i;
	char	buffer[51];
	int		retval;

	size = 0;
	while ((retval = read(file->fd, buffer, 50)) > 0)
	{
		buffer[retval] = '\0';
		i = 0;
		while (buffer[i] && (buffer[i] == ' ' || buffer[i] == '\t'))
		{
			file->col += 1;
			i++;
		}
		size += i;
		if (i != retval)
			break;
	}
	if (retval == -1)
		ft_error(env, file, READ_ERROR);
	else if (retval == 0)
		file->mode = DONE;
	else
		ft_offset_head(env, file, size);
}

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

int			ft_parse_while(t_file *file, char *containing, char **line)
{
	char	buf[51];
	int		i;
	int		size;
	int		retval;

	size = 0;
	while ((retval = read(file->fd, buf, 50)) > 0)
	{
		i = 0;
		while(buf[i] && ft_is_one_of(buf[i], containing))
			i++;
		size += i;
		if (i != retval)
			break;
	}
	if (retval == -1)
		return (ft_error(ft_get_env(), file, READ_ERROR));
	if (retval == 0)
		file->mode = DONE;
	*line = (char*)ft_malloc(sizeof(char) * (size + 1));
	ft_offset_head(ft_get_env(), file, 0);
	retval = read(file->fd, *line, size);
	if (retval == -1)
	{
		free(*line);
		*line = NULL;
		return (ft_error(ft_get_env(), file, READ_ERROR));
	}
	(*line)[retval] = '\0';
	ft_offset_head(ft_get_env(), file, size);
	ft_offset_lines(ft_get_env(), file, *line);
	return (1);
}



int			ft_parse_until(t_file *file, char *limit, char **line, int skipping)
{
	char	buf[51];
	int		i;
	int		size;
	int		retval;

	size = 0;
	while ((retval = read(file->fd, buf, 50)) > 0)
	{
		i = 0;
		while(buf[i] && !ft_is_one_of(buf[i], limit))
			i++;
		size += i;
		if (i != retval)
			break;
	}
	if (retval == -1)
		return (ft_error(ft_get_env(), file, READ_ERROR));
	if (retval == 0)
		file->mode = DONE;
	*line = (char*)ft_malloc(sizeof(char) * (size + 1));
	ft_offset_head(ft_get_env(), file, 0);
	retval = read(file->fd, *line, size);
	if (retval == -1)
	{
		free(*line);
		*line = NULL;
		return (ft_error(ft_get_env(), file, READ_ERROR));
	}
	(*line)[retval] = '\0';
	ft_offset_head(ft_get_env(), file, size + (skipping ? 1 : 0));
	ft_offset_lines(ft_get_env(), file, *line);
	return (1);
}

// faire fonction de parsing tant que les chars contiennent ... 
// faire fonction de parsing tant que les chars ne contiennent PAS

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
	t_token	token;
	
	ft_token_init(&token, STRING, file->col, file->line);
	ft_parse_until(file, "\"", &(token.value), 1);
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

// return op or register or UNKNOWN

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
	if (buf[0] == LABEL_CHAR)
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
	(void)file;
	file->mode = DONE;
}

void		ft_parse_token(t_env *env, t_file *file)
{
	char	buf[51];
	int		retval;

	(void)env;
	if ((retval = read(file->fd, buf, 50)) > 0)
	{
		buf[retval] = 0;
		if (buf[0] == COMMENT_CHAR && ft_offset_head(env, file, 1) && (file->col += 1))
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
			ft_parse_unknown(file);
	}
	else if (retval == -1)
		ft_error(env, file, READ_ERROR);
	else if (retval == 0)
		file->mode = DONE;
//	ft_printf("PARSE TOKEN RET >%s<\n", buf);
}

char		*ft_tokentype_string(int type)
{
	if (type == COMMAND)
		return ("COMMAND");
	else if (type == STRING)
		return ("STRING");
	else if (type == COMMENT)
		return ("COMMENT");
	else if (type == LABEL)
		return ("LABEL");
	else if (type == OPERATION)
		return ("OPERATION");
	else if (type == PARAM)
		return ("PARAM");
	else if (type == NEWLINE)
		return ("NEWLINE");
	else if (type == SEPARATOR)
		return ("SEPARATOR");
	else if (type == REGISTER)
		return ("REGISTER");
	else if (type == DIRECT)
		return ("DIRECT");
	else if (type == NUMBER)
		return ("NUMBER");
	else
		return ("UNKNOWN");
}

void		ft_dump_tokens(t_file *file)
{
	t_token	*token;

	token = file->tokens;
	while (token)
	{
		ft_printf("token of type : %s\n", ft_tokentype_string(token->type));
		ft_printf("\tits value is : %s\n", token->value);
		ft_printf("\tits converted value is : %d\n", token->int_value);
		ft_printf("\tat pos [%d:%d]\n", token->line, token->col);
		token = token->next;
	}
}

int			ft_parse_file(t_env *env, t_file *file)
{
	while (file->mode != DONE && file->mode != CRASH)
	{
		ft_skip_spaces(env, file);
		ft_parse_token(env, file);
//		file->mode = DONE;
	}
	ft_dump_tokens(file);
	return (1);
}

int			ft_write_file(t_env *env, t_file *file)
{
	(void)env;
	(void)file;
	ft_printf("writing file !\n");
	return (1);
}


void		ft_parse_files(t_env *env)
{	
	t_file	*ptr;
	t_file	*tmp;

	ptr = env->files;
	while (ptr)
	{
		if (!(ft_open_file(env, ptr)))
		{
			tmp = ptr;
			ptr = ptr->next;
//			ft_delete_file(env, tmp); pareil que dessous
			continue;
		}
		else if (!(ft_parse_file(env, ptr)))
		{
			close(ptr->fd);
			tmp = ptr;
			ptr = ptr->next;
//			ft_delete_file(env, tmp); pareil que dessous
			continue;
		}
		else if (!(ft_write_file(env, ptr)))
		{
			close(ptr->fd);
			tmp = ptr;
			ptr = ptr->next;
//			ft_delete_file(env, tmp); pareil que dessous
			continue;
		}
		close(ptr->fd);
		tmp = ptr;
//		ft_delete_file(env, tmp); penser a decomenter pour retrouver les files dans le dump
		ptr = ptr->next;
	}
}

int			main(int ac, char **av)
{
	t_env	env;

	ft_init_env(&env, av[0]);
	ft_set_env(&env);
	ft_parse_args(ac, av, &env);
	ft_parse_files(&env);
	ft_dump_env(&env);
	ft_free_env(&env);
	return (0);
}
