/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:18 by toliver           #+#    #+#             */
/*   Updated: 2019/11/22 06:48:17 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_pow2(int pow)
{
	int		i;
	int		value;

	if (pow < 0)
		return (0);
	value = 1;
	i = 0;
	while (i < pow)
	{
		value *= 2;
		i++;
	}
	return (value);
}

int			ft_strchr_pos(char *str, int c)
{
	char	*val;

	val = ft_strchr(str, c);
	if (val == NULL)
		return (-1);
	return ((int)(val - str));
}

int			ft_crash(t_env *env, int error)
{
	env->mode = CRASH;
	env->error.value = error;
	return (0);
}

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

int			ft_is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f'
			|| c == ' ')
		return (1);
	return (0);
}

int			ft_error(t_env *env, t_file *file, int error)
{
	env->mode = ERROR;
	env->error.value = error;
	ft_dprintf(2, "%s: %s: %s\n", env->prog_name, file->filename, strerror(errno));
	return (0);
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

int			ft_parsing_error(t_env *env, int error, char *str, t_file *file)
{
	env->mode = ERROR;
	if (error == UNEXPECTED_TOKEN)	
		ft_dprintf(2, "%s: %s: unexpected token at [%03d:%03d]: %c\n", env->prog_name, file->filename, file->line + 1, file->column + 1, *str);
	else if (error == NAME_TOO_LONG)
		ft_dprintf(2, "%s: %s: Champion name too long (Max length %d)\n", env->prog_name, file->filename, PROG_NAME_LENGTH);
	else if (error == REDEFINED_NAME)
		ft_dprintf(2, "%s: %s: redefined '.name' at [%03d:%03d]\n", env->prog_name, file->filename, file->line + 1, file->column + 1);
	else if (error == REDEFINED_COMMENT)
		ft_dprintf(2, "%s: %s: redefined '.comment' at [%03d:%03d]\n", env->prog_name, file->filename, file->line + 1, file->column + 1);
	else
		ft_dprintf(2, "unknown error !\n");
	return (0);
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
		return (ft_parsing_error(env, UNEXPECTED_TOKEN, buf, file));
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
	file->column += size;
	file->offset = lseek(file->fd, file->offset + size, SEEK_SET);
	if (file->offset == -1)
		return (ft_error(env, file, LSEEK_ERROR));
	return (1);
}

int			ft_offset_head(t_file *file, char *str, int size)
{
	file->offset = lseek(file->fd, file->offset + size, SEEK_SET);
	if (file->offset == -1)
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
	file->offset = lseek(file->fd, file->offset + i + 1, SEEK_SET);
	if (file->offset == -1)
		return (ft_error(env, file, LSEEK_ERROR));
	if (!(file->name = ft_strsub(buf, 1, i - 1)))
		return (ft_crash(env, MALLOC_FAIL));
	env->mode = PARSING_FIRSTLINES;
	return (1);
}

void		ft_parse_comment_cmd(t_env *env, t_file *file)
{
	char	buf[11];
	int		retval;

	retval = read(file->fd, buf, 10);
	buf[retval] = '\0';
	ft_printf(">%s<\n", buf);
	(void)env;
	(void)file;
	env->mode = PARSING_INSTRUCTIONS;
}

void		ft_parse_comment(t_env *env, t_file *file)
{
	(void)env;
	(void)file;
	env->mode = PARSING_INSTRUCTIONS;
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

void		ft_dump_file(t_file *file)
{
	ft_printf("file name : %s\n", file->filename);
	ft_printf("file fd : %d\n", file->fd);
	ft_printf("file offset = %lld\n", file->offset);
	ft_printf("file .name : %s\n", file->name);
	ft_printf("file .comment : %s\n", file->comment);
	ft_printf("file actual line : %zu\n", file->line);
	ft_printf("file actual column : %zu\n", file->column);
//	ft_dump_instructions(file);
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

void		ft_parse_instructions(t_env *env, t_file *file)
{
	(void)file;
	env->mode = PARSING_DONE;
	// no need explanation here
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

void		ft_dump_env(t_env *env)
{
	ft_printf("env mode = %d\n", env->mode);
	ft_printf("env error = %d\n", env->error.value);
	ft_printf("flags = %d, en binaire : %b\n", env->flags, env->flags);
}

void		ft_usage(t_error *error)
{
	if (error->value == WRONG_FLAGS)
		ft_dprintf(2, "illegal option -- %c\n", error->flag_error);
	ft_dprintf(2, "usage: ./asm [-%s] file ...\n", FLAGS);	
}

void		ft_print_crash(char *program, t_error *error)
{
	ft_dprintf(2, "%s: ", program);
	if (error->value == NO_PARAMS || error->value == WRONG_FLAGS)
		ft_usage(error);
	else if (error->value == MALLOC_FAIL)
		ft_dprintf(2, "malloc failed : %s\n", strerror(errno));
	else
		ft_putstr_fd("unknown error\n", 2);
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
