/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboukrou <lboukrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:18:38 by toliver           #+#    #+#             */
/*   Updated: 2020/01/05 03:20:55 by lboukrou         ###   ########.fr       */
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
	WRITE_ERROR,
};

enum e_type
{
	COMMAND = 1,
	COMMAND_NAME,
	COMMAND_COMMENT,
	STRING,
	COMMENT,
	LABEL,
	OPERATION,
	PARAM,
	NEWLINE,
	INDIRECT,
	INDIRECT_LABEL,
	DIRECT,
	DIRECT_LABEL,
	SEPARATOR,
	REGISTER,
	NUMBER,
	INSTRUCTION,
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
	struct s_token	*prev;
}					t_token;

enum e_fileparsing_mode
{
	PARSING,
	CRASH,
	DONE,
	CONTAIN_ERRORS,
};

typedef struct		s_label
{
	struct s_label	*next;
	char			*value; // ne pas free, assigne token->value
	int				mem; 
	int				col;
	int				line;
}					t_label;

typedef struct		s_file
{
	struct s_file	*next;
	char			*filename; // ne pas free, assigne le av[i] correspondant;
	int				fd;
	int				line;
	int				col;
	off_t			offset;
	int				mode;
	t_token			*tokens;
}					t_file;

typedef struct		s_param
{
	int				type;
	int				value_type;
	char			*value;
	int				int_value;
	int				len;
	int				line;
	int				col;
}					t_param;

typedef struct		s_operation
{
	struct s_operation	*next;
	struct s_operation	*prev;
	char				opc;
	char				*name; // ne pas free, assigne g_op_opcode
	t_param				params[3];
	int					p_num;
	int					mem;
	int					len;
	int					encoding;
	int					is_encoding_needed;
	int					line;
	int					col;
}					t_operation;

typedef struct		s_program
{
	int				fd;
	char			*filename;
	t_operation		*operations;
	t_label			*label;
	t_header		header;
}					t_program;

typedef struct		s_env
{
	char			*prog_name; // ne pas free, assigne av[0]
	int				flags;
	t_file			*files;
	t_program		prog;
}					t_env;

/*
** CHAMPION PROGRAM FUNC
*/

int					ft_init_prog(t_env *env, t_file *file);
void				ft_clear_prog(t_program *prog);

/*
** LABEL FUNC
*/

int					ft_check_labels(t_file *file, t_program *prog, t_token *token);
void				ft_free_label(t_program *prog);
int					ft_add_label(t_file *file, t_program *prog, char *label, t_token *token);

/*
** OPERATION FUNC
*/

t_op				*ft_fetch_op(char *str);
void				ft_free_op(t_program *prog);
int					ft_check_op(t_file *file, t_program *prog, t_token **token);

/*
** PARAMS FUNC
*/

int					ft_create_param(t_file *file, t_operation *operation, t_token **token, t_op const*op);
int					ft_check_params_types(t_file *file, t_operation *operation, t_op const*op);

/*
** WRITING FUNC
*/

int					ft_check_header(t_file *file, t_program *prog);
int					ft_open_cor_file(t_program *prog, t_env *env, t_file *file);

/*
** PARSING OPERATION FUNC UTILS
*/

int					ft_pass_newline(t_file *file, t_token **token);
int					ft_pass_comm(t_file *file, t_token **token);
int					ft_pass_newline_comm(t_file *file, t_token **token);
void				ft_parse_args(int ac, char **av, t_env *env);

/*
** ERROR FUNC
*/

void				ft_usage(void);
void				ft_wrong_flag(t_env *env, char c);
void				ft_crash(int error);
int					ft_error(t_env *env, t_file *file, int error);
int					ft_lexical_error(t_file *file, t_token *token);
int					ft_syntax_error(t_file *file, t_token *token);


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

size_t				ft_strspn(const char *s, const char *charset);;
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
t_token				*ft_last_token(t_file *file);
void				ft_parse_unknown(t_file *file);



/*
** TOKEN INIT FUNC
*/

void				ft_add_token(t_file *file, t_token *token);
void				ft_token_init(t_token *token, int type, int col, int line);

/*
** PARSE FILES FUNC
*/

void				ft_parse_files(t_env *env);
int					ft_parse_file(t_env *env, t_file *file);
int					ft_write_file(t_env *env, t_file *file);
void				ft_delete_file(t_env *env, t_file *file);
int					ft_open_file(t_env *env, t_file *file);




/*
** TOKEN PARSE FUNC
*/

void				ft_parse_indirect_label(t_file *file);
void				ft_parse_direct(t_file *file);
void				ft_parse_indirect(t_file *file);
void				ft_parse_register(t_file *file, t_token *token, size_t ret);
int					ft_parse_number(t_file *file, t_token *token);


/*
** TOKEN PARSE IDENTIFIER FUNC
*/

int					ft_is_number(t_token *token);
int					ft_is_label(t_file *file);
int					ft_is_reg(char *str);


/*
** TOKEN PARSE INSTRUCTIONS FUNC
*/

void				ft_parse_instruction(t_file *file);
void				ft_parse_instruction_direct(t_file *file, t_token *token,
										t_token *last, size_t ret);


/*
** TOKEN TYPE FUNC
*/

void				ft_parse_comment(t_file *file);
void				ft_parse_cmd(t_file *file);
void				ft_parse_string(t_file *file);
void				ft_parse_newline(t_file *file);
void				ft_parse_separator(t_file *file);


/*
** PRINTING FUNC
*/

char				*ft_type_param(t_param *param);
char				*ft_tokentype_string(int type);
void				ft_dump_tokens(t_file *file);
void				ft_dump_env(t_env *env);
void				ft_dump_files(t_file *files);
void				ft_dump_op(t_program *prog);
void				ft_dump_label(t_program *prog);
void				ft_dump_prog(t_program *prog);

#endif
