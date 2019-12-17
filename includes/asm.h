/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:18:38 by toliver           #+#    #+#             */
/*   Updated: 2019/12/17 06:38:37 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
#define ASM_H
#include <unistd.h>
#include <sys/errno.h>
#include <fcntl.h>
#include "libft.h"
#include "libftprintf.h"
#include "op.h"

#define FLAGS "a"

enum e_mode 
{
	PARSING_FLAGS,
	PARSING_FILES,
	PARSING_COMMANDS,
};

enum e_error
{
	MALLOC_FAIL,
	OPEN_ERROR,
	READ_ERROR,
	LSEEK_ERROR,
};

enum e_type
{
	COMMAND,
	STRING,
	COMMENT,
	LABEL,
	OPERATION,
	PARAM,
	NEWLINE,
	DIRECT,
	SEPARATOR,
	REGISTER,
	NUMBER,	
	UNKNOWN,
};
// parse par token puis parse les tokens

typedef struct		s_token
{
	int				type;
	char			*value;
	int				int_value;
	int				col;
	int				line;
	struct s_token	*next;
}					t_token;

enum e_fileparsing_mode
{
	PARSING,
	CRASH,
	DONE,
	CONTAIN_ERRORS,
};

typedef struct		s_file
{
	char			*filename; // ne pas free, assigne le av[i] correspondant;
	int				fd;
	int				line;
	int				col;
	off_t			offset;
	int				mode;
	t_token			*tokens;
	struct s_file	*next;
}					t_file;

typedef struct		s_env
{
	char			*prog_name; // ne pas free, assigne av[0]
	int				flags;
	t_file			*files;
}					t_env;

typedef struct		s_program
{
	int			fd;
	char			*filename;
	char			*name;
	char			*comment;
//	t_operation		*operations;
}					t_program;

/*
	STRUCTURES POUR LA CONVERSION EN OPERATIONS

typedef struct		s_param
{
	int				type;
	int				value_type;
	char			*value;
	int				int_value;
}					t_param;

typedef struct		s_label
{
	char			*value;
	struct s_label	*next;
}					t_label;

typedef struct		s_operation
{
	t_label			*labels;
	unsigned		op_code;
	t_param			params[3];	
}					t_operation;

typedef struct		s_program
{
	char			*filename;
	char			*name;
	char			*comment;
	t_operation		*operations;
}					t_program;
*/

/*
** PARSING FUNC
*/

void				ft_parse_args(int ac, char **av, t_env *env);

/*
** ERROR FUNC
*/

void				ft_usage(void);
void				ft_wrong_flag(t_env *env, char c);
void				ft_crash(int error);
int				ft_error(t_env *env, t_file *file, int error);
int				ft_lexical_error(t_file *file);

/*
** ENV FUNC
*/

t_env				*ft_get_env(void);
void				ft_set_env(t_env *env);
void				ft_init_env(t_env *env, char *prog_name);
void				ft_free_env(t_env *env);

/*
** FILES FUNC
*/

void				ft_free_file(t_file *file);
void				ft_free_files(t_env *env);

/*
** UTILS FUNC
*/

void				*ft_malloc(size_t size);
int					ft_pow2(int pow);
int					ft_strchr_pos(char *str, int c);
int					ft_is_one_of(char c, char *lookfor);

/*
** PARSING UTILS FUNC
*/

int					ft_parse_while(t_file *file, char *containing, char **line);
int					ft_parse_until(t_file *file, char *limit, char **line, int skipping);
void				ft_skip_spaces(t_env *env, t_file *file);
int					ft_offset_lines(t_env *env, t_file *file, char *str);
int					ft_offset_head(t_env *env, t_file *file, size_t size);

/*
** TOKEN FUNC
*/

void				ft_parse_token(t_env *env, t_file *file);

/*
** PRINTING FUNC
*/

void				ft_dump_tokens(t_file *file);
void				ft_dump_env(t_env *env);
void				ft_dump_files(t_file *files);
#endif
