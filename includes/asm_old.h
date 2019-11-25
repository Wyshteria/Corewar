/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:18:38 by toliver           #+#    #+#             */
/*   Updated: 2019/11/25 20:24:00 by toliver          ###   ########.fr       */
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

typedef struct		s_env
{
	char			*prog_name;
	int				mode;
//	t_error			error;
	int				flags;
}					t_env;


enum e_mode 
{
	CRASH,
	ERROR,
	PARSING_ARGS,
	PARSING_FLAGS,
	PARSING_FILES,
	PARSING_OPENFILE,
	PARSING_FIRSTLINES,
	PARSING_NAME_CMD,
	PARSING_COMMENT_CMD,
	PARSING_COMMENT,
	PARSING_INSTRUCTIONS,
	PARSING_DONE,
	FINISHED
};

enum e_parsing_error
{
	UNEXPECTED_TOKEN,
	NAME_TOO_LONG,
	REDEFINED_NAME,
	REDEFINED_COMMENT,
	MISSING_NAME,
	MISSING_COMMENT
};

enum e_error
{
	NO_PARAMS,
	WRONG_FLAGS,
	MALLOC_FAIL,
	OPEN_ERROR,
	READ_ERROR,
	LSEEK_ERROR,
	PARSING_ERROR,
};

typedef struct		s_error
{
	int				value;
	char			flag_error;
}					t_error;

union				u_param_types
{
	char			*label;
	int				num;
};

typedef struct				s_param
{
	char					type;
	char					value_type;
	union u_param_types		value;
}							t_param;

typedef struct				s_instruction
{
	char					*label;
	unsigned int			opcode;
	t_param					params[4];
	struct s_instruction	*next;
}							t_instruction;

typedef struct		s_file
{
	char			*filename; // do not free, is given the av value
	int				fd;
	off_t			offset;
	size_t			line;
	size_t			column;
	char			*name;
	char			*comment;
	t_instruction	*instructions;
}					t_file;

static t_op    op_tab[17] =
{
	{0, 0, {0}, 0, 0, 0, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
};




/*
**	ERROR FUNCTIONS
*/
void			ft_usage(t_error *error);
void			ft_print_crash(char *program, t_error *error);
int				ft_parsing_error(t_env *env, int err, char *str, t_file *file);
int				ft_error(t_env *env, t_file *file, int error);
int				ft_crash(t_env *env, int error);


/*
**	PRINTING FUNCTIONS
*/

void			ft_dump_env(t_env *env);
void			ft_dump_file(t_file *file);
void			ft_dump_instructions(t_instruction *op);


/*
**	UTILS FUNCTIONS
*/
int				ft_pow2(int pow);
int				ft_strchr_pos(char *str, int c);
int				ft_is_whitespace(char c);

#endif
