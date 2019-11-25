/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:18 by toliver           #+#    #+#             */
/*   Updated: 2019/11/25 22:16:39 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_parse_flags(t_env *env, char *flag)
{
	int		i;
	int		pos;
	int		flags;

	i = 0;
	flags = 0;
	if (flag[0] != '-' || (flag[0] == '-' && flag[1] == '-'))
	{
		env->mode = PARSING_FILES;
		return (0);
	}
	flag++;
	while (flag[i])
	{
		if ((pos = ft_strchr_pos(FLAGS, flag[i])) == -1)
		{
			env->error.flag_error = flag[i];
			return (ft_crash(env, WRONG_FLAGS));
		}
		flags = flags | ft_pow2(pos);
		i++;
	}
	env->flags |= flags;
	return (1);
}

int			ft_offset_head(t_env *env, t_file *file, char *str, int size)
{
	int		i;
	
	file->offset = lseek(file->fd, file->offset + size, SEEK_SET);
	if (file->offset == -1)
		return (ft_error(env, file, LSEEK_ERROR));
	i = 0;
	while (str && str[i] && i < size)
	{
		file->column += 1;
		if (str[i] == '\n')
		{
			file->line += 1;
			file->column = 0;
		}
		i++;
	}
	return (1);
}

int			ft_remove_spaces(t_env *env, t_file *file)
{
	int		size;
	char	buffer[51];
	int		retval;
	int		i;

	size = 0;
	i = 0;
	while ((retval = read(file->fd, buffer, 50)) > 0)
	{
		buffer[retval] = '\0';
		i = 0;
		while (buffer[i] && ft_is_whitespace(buffer[i]))
		{
			file->column += 1;
			if (buffer[i] == '\n')
			{
				file->line += 1;
				file->column = 0;
			}
			i++;
		}
		size += i;
		if (i != retval)
			break;
	}
	if (retval == -1)
		return (ft_error(env, file, READ_ERROR));
	file->offset = lseek(file->fd, file->offset + size, SEEK_SET);
	if (file->offset == -1)
		return (ft_error(env, file, LSEEK_ERROR));
	return (1);
}

int			ft_parse_unknown_firstline(t_env *env, t_file *file)
{
	char	buf[9];
	int		retval;
	int		size;

	if ((retval = read(file->fd, buf, 8)) == -1)
		return (ft_error(env, file, READ_ERROR));
	buf[retval] = '\0';
	if (!ft_strncmp(buf, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		env->mode = PARSING_NAME_CMD;
	else if (!ft_strncmp(buf, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		env->mode = PARSING_COMMENT_CMD;
	else if (buf[0] == COMMENT_CHAR)
		env->mode = PARSING_COMMENT;
	else
	{
		env->mode = PARSING_INSTRUCTIONS;
		if (!(ft_offset_head(env, file, NULL, 0)))
			return (0);
		return (1);
	}
	if (env->mode == PARSING_COMMENT)
		size = 1;
	else if (env->mode == PARSING_NAME_CMD)
	{
		size = ft_strlen(NAME_CMD_STRING);
		if (file->name != NULL)
			return (ft_parsing_error(env, REDEFINED_NAME, buf, file));
	}
	else if (env->mode == PARSING_COMMENT_CMD)
	{
		size = ft_strlen(COMMENT_CMD_STRING);
		if (file->comment != NULL)
			return (ft_parsing_error(env, REDEFINED_COMMENT, buf, file));
	}
	else
		size = 0;
	if (!(ft_offset_head(env, file, buf, size)))
		return (0);
	return (1);
}

int			ft_parse_name_cmd(t_env *env, t_file *file)
{
	char	buf[PROG_NAME_LENGTH + 3];
	int		retval;
	int		i;

	i = 1;
	if ((retval = read(file->fd, buf, PROG_NAME_LENGTH + 2)) == -1)
		return (ft_error(env, file, READ_ERROR));
	buf[retval] = '\0';
	if (buf[0] != '"')
		return (ft_parsing_error(env, UNEXPECTED_TOKEN, buf, file));
	while (buf[i] && buf[i] != '"')
		i++;
	if (i > PROG_NAME_LENGTH + 1)
		return (ft_parsing_error(env, NAME_TOO_LONG, buf, file));
	if (!(ft_offset_head(env, file, buf, i + 1)))
		return (0);
	if (!(file->name = ft_strsub(buf, 1, i - 1)))
		return (ft_crash(env, MALLOC_FAIL));
	env->mode = PARSING_FIRSTLINES;
	return (1);
}

int			ft_parse_comment_cmd(t_env *env, t_file *file)
{
	char	buf[COMMENT_LENGTH + 3];
	int		retval;
	int		i;

	i = 1;
	if ((retval = read(file->fd, buf, COMMENT_LENGTH + 2)) == -1)
		return (ft_error(env, file, READ_ERROR));
	buf[retval] = '\0';
	if (buf[0] != '"')
		return (ft_parsing_error(env, UNEXPECTED_TOKEN, buf, file));
	while (buf[i] && buf[i] != '"')
		i++;
	if (i > COMMENT_LENGTH + 1)
		return (ft_parsing_error(env, NAME_TOO_LONG, buf, file));
	if (!(ft_offset_head(env, file, buf, i + 1)))
		return (0);
	if (!(file->comment = ft_strsub(buf, 1, i - 1)))
		return (ft_crash(env, MALLOC_FAIL));
	env->mode = PARSING_FIRSTLINES;
	return (1);
}

int			ft_parse_comment(t_env *env, t_file *file)
{
	int		size;
	char	buffer[51];
	int		retval;
	int		i;

	size = 0;
	i = 0;
	while ((retval = read(file->fd, buffer, 50)) > 0)
	{
		buffer[retval] = '\0';
		i = 0;
		while (buffer[i])
		{
			file->column += 1;
			if (buffer[i] == '\n')
			{
				file->line += 1;
				file->column = 0;
				i++;
				break;
			}
			i++;
		}
		size += i;
		if (i != retval)
			break;
	}
	if (retval == -1)
		return (ft_error(env, file, READ_ERROR));
	file->offset = lseek(file->fd, file->offset + size, SEEK_SET);
	if (file->offset == -1)
		return (ft_error(env, file, LSEEK_ERROR));
	env->mode = PARSING_FIRSTLINES;
	return (1);
}

int			ft_parse_firstlines(t_env *env, t_file *file)
{
	while (env->mode == PARSING_FIRSTLINES || env->mode == PARSING_NAME_CMD ||
			env->mode == PARSING_COMMENT_CMD || env->mode == PARSING_COMMENT)
	{
		ft_remove_spaces(env, file);
		if (env->mode == PARSING_FIRSTLINES)
			ft_parse_unknown_firstline(env, file);
		else if (env->mode == PARSING_NAME_CMD)
			ft_parse_name_cmd(env, file);
		else if (env->mode == PARSING_COMMENT_CMD)
			ft_parse_comment_cmd(env, file);
		else if (env->mode == PARSING_COMMENT)
			ft_parse_comment(env, file);
	}
	if (env->mode != ERROR && env->mode != CRASH && env->mode != FINISHED)
		env->mode = PARSING_INSTRUCTIONS;
	return (1);
}

void		ft_open_file(t_env *env, t_file *file, char *file_name)
{
	int		fd;

	fd = open(file_name, O_RDONLY);
	file->fd = fd;
	file->filename = file_name;
	file->name = NULL;
	file->comment = NULL;
	file->instructions = NULL;
	file->offset = 0;
	file->column = 0;
	file->line = 0;
	if (fd == -1)
	{
		env->mode = ERROR;
		ft_error(env, file, OPEN_ERROR); 
		return;
	}
	env->mode = PARSING_FIRSTLINES;	
}

int			ft_add_op(t_env *env, t_file *file, t_instruction *op)
{
	t_instruction	*new_op;
	t_instruction	*ptr;

	if (!(new_op = (t_instruction*)malloc(sizeof(t_instruction))))
		return (ft_crash(env, MALLOC_FAIL));
	ft_memcpy(new_op, op, sizeof(t_instruction));
	if (file->instructions == NULL)
		file->instructions = new_op;
	else
	{
		ptr = file->instructions;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_op;
	}
	return (1);
}

void		ft_skip_spaces(char *str, int *i, t_file *file)
{
	while (str[*i] == ' ' || str[*i] == '\t')
	{
		(*i)++;
		file->column++;
	}
}


void		ft_parse_op(t_env *env, t_file *file, char *str, t_instruction *op)
{
	int		i;

	i = 0;
	(void)env;
	(void)op;
	ft_skip_spaces(str, &i, file);
	ft_parse_label_and_token(str, &i, file, op);
	ft_skip_spaces(str, &i, file);
//	ft_parse_op(str, &i, file);

	ft_printf(">%s<\n", str + i);
}

int			ft_parse_instructions(t_env *env, t_file *file)
{
	char			*str;
	int				retval;
	t_instruction	op;
	if (!file->name)
		return (ft_parsing_error(env, MISSING_NAME, NULL, file));
	else if (!file->comment)
		return (ft_parsing_error(env, MISSING_COMMENT, NULL, file));
	while ((retval = ft_get_next_line(file->fd, &str)) > 0)
	{
		ft_bzero(&op, sizeof(t_instruction));
		ft_parse_op(env, file, str, &op);
		free(str);
		//ft_add_op(env, file, &op);
		file->column = 0;
		file->line += 1;
	}
	if (retval == -1)
		return (ft_crash(env, MALLOC_FAIL));
	env->mode = PARSING_DONE;
	return (1);
}

void		ft_parse_files(t_env *env, char *file_name)
{
	t_file	file;

	env->mode = PARSING_OPENFILE;
	while (env->mode != ERROR && env->mode != CRASH && env->mode != PARSING_DONE)
	{
		if (env->mode == PARSING_OPENFILE)
			ft_open_file(env, &file, file_name);
		else if (env->mode == PARSING_FIRSTLINES)
			ft_parse_firstlines(env, &file);
		else if (env->mode == PARSING_INSTRUCTIONS)
			ft_parse_instructions(env, &file);
	}
	if (env->mode != ERROR || (env->mode == ERROR && env->error.value != OPEN_ERROR))
		close(file.fd);
	if (env->mode != CRASH)
		env->mode = PARSING_FILES;
	ft_dump_file(&file);
	/*
		ft_write_file(&file);
		ft_free_file(&file);
	*/
}

void		ft_parse_args(int ac, char **av, t_env *env)
{
	int		i;

	i = 0;
	env->mode = PARSING_FLAGS;
	if (ac == 0)
		ft_crash(env, NO_PARAMS);
	while (i < ac && env->mode != CRASH)
	{
		if (env->mode == PARSING_FLAGS)
		{
			if (ft_parse_flags(env, av[i]))
				i++;
		}
		if (env->mode == PARSING_FILES)
		{
			ft_parse_files(env, av[i]);
			i++;
		}
	}
	if (env->mode != CRASH)
		env->mode = FINISHED;
}

int			main(int ac, char **av)
{
	t_env	env;

	env.prog_name = av[0];
	env.mode = PARSING_ARGS;
	ft_parse_args(ac - 1, av + 1, &env);
	if (env.mode != CRASH)
		ft_putstr("ca crash pas !\n");
	if (env.mode == CRASH)
		ft_print_crash(env.prog_name, &env.error);
//	ft_dump_env(&env);
	return (0);
}
