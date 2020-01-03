/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 01:38:07 by toliver           #+#    #+#             */
/*   Updated: 2020/01/03 16:28:50 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
#define VM_H
#include <unistd.h>
#include <sys/errno.h>
#include <fcntl.h>
#include "libft.h"
#include "libftprintf.h"
#include "op.h"
#include <stdint.h>
#include "display.h"

/*
#define CONCATABLE_FLAGS "a"
#define PARAMS_FLAGS "dsv"
*/
#define AFF_FLAG 0x1 // a
#define DUMP_FLAG 0x2 // d
#define CYCLE_DUMP_FLAG 0x4 // s
#define VERBOSE_FLAG 0x8 // v
#define NCURSES_FLAG 0x10 // nc
#define FORBIDDEN_NC_FLAGS 0xE

#define VERBOSE_LIVES_FLAG 0x1
#define VERBOSE_CYCLES_FLAG 0x2
#define VERBOSE_OPERATIONS_FLAG 0x4
#define VERBOSE_DEATH_FLAG 0x8
#define VERBOSE_PC_MOVEMENT_FLAG 0x16

typedef struct				s_params_list
{
	char					*param;
	struct s_params_list	*next;
}							t_params_list;

enum				e_parsing_modes
{
	PARSING_RUNNING,
	PARSING_ERROR,
	PARSING_CRASH,
	PARSING_DONE,
};

enum				e_parsing_errors
{
	UNKNOWN_FLAG,
	FLAG_WITH_NC_ERROR,
	NC_WITH_FLAGS_ERROR,
	PARAM_FLAG_WRONG,
	PARAM_MISSING,
	CHAMP_MISSING,
	PARAM_NEGATIVE,
	PARSING_OVERFLOW,
};

enum				e_champ_error
{
	OPEN_ERROR,
	READ_ERROR,
	TOO_SHORT,
	MAGIC_ERROR,
	NAME_TOO_LONG,
	COMMENT_TOO_LONG,
	SIZE_ERROR,
};

enum				e_arena_error
{
	NOT_ENOUGH_SPACE,
	MALLOC_FAIL,
	NO_CHAMPIONS,
};

enum				e_op_type
{
	NOTHING,
	LIVE,
	LD,
	ST,
	ADD,
	SUB,
	AND,
	OR,
	XOR,
	ZJMP,
	LDI,
	STI,
	FORK,
	LLD,
	LLDI,
	LFORK,
	AFF,
};

union				u_converter
{
	char			value[4];
	int32_t			real_value;
};

typedef struct		s_champ
{
	int				hasnumber;
	int				number;
	t_header		header;
	int				fd;
	int				offset;
	char			*filename;
	char			*content;
	struct s_champ	*next;
}					t_champ;

typedef struct		s_byte
{
	unsigned char	value;
	int				writer;
}					t_byte;

typedef struct		s_reg
{
	char 			mem[REG_SIZE];
} 					t_reg;

typedef struct			s_process
{
	int 				pid;
	int					pos;
	unsigned char		opcode_value;
	int					owner;
	int					cycles_to_exec;
	t_reg				reg[REG_NUMBER];
	int					op_size;
	int					carry;
	int					live_number;
	size_t				last_live;
	int					need_refresh;
	struct s_process	*next;
}						t_process;

typedef struct		s_opcode
{
	unsigned int	opcode;
	char			*opcode_name;
	int				params_number;
	int				need_encoding_byte;
	char			encoding_byte;
	int				dir_two_bytes;
	int32_t			params[REG_NUMBER];
	int				params_types[REG_NUMBER];
	int32_t			params_parsed[REG_NUMBER];
	int				size;
	int				is_valid;
	int				flag;
//	int				pos;
}					t_opcode;

typedef struct		s_arena
{
	int				pid;
	int				maxx;
	int				maxy;
	int				op_per_line;
	int				line_number;
	t_byte			arena[MEM_SIZE];
	t_process		*process;
	size_t			cycles;
	int				mode;
	int				actual_cycles_to_die;
	int				cycles_to_die;
	int				check_number;
	int				last_live;
}					t_arena;

typedef struct		s_env
{
	char			*prog_name;
	int				ac;
	unsigned int	flags;
	size_t			dump_cycles;
	size_t			cycle_dump_cycles;
	int				verbose_level;
	t_champ			*champs;
	t_arena			arena;
}					t_env;


/*
** DUMP FUNCTIONS
*/

void		ft_dump_env(t_env *env);
void		ft_dump_champs(t_env *env);
void		ft_dump_header(t_header *header);
void		ft_dump_flags(t_env *env);
void		ft_dump_verbose_flags(t_env *env);
void		ft_dump_arena(t_arena *arena);
void		ft_dump_process(t_process *process);
void		ft_dump_op(t_opcode *op);
void		ft_dump_process(t_process *process);
void		ft_dump_all_process(t_arena *arena);
/*
** UTILS FUNCTIONS
*/

uint32_t	ft_swap(uint32_t toswap);
int			ft_is_containing_other_than(char *str, char *containing);
int			ft_pow2(int pow);
int			ft_strchr_pos(char *str, int c);
int			ft_is_one_of(char c, char *lookfor);
void		*ft_malloc(size_t size);
t_champ		*ft_get_champ(int champnumber);
/*
** ENV FUNCTIONS
*/

t_env		*ft_get_env(void);
void		ft_set_env(t_env *env);
int			ft_env_init(t_env *env, char *progname, int ac);
void		ft_free_env(t_env *env);
/*
** PARAM PARSING FUNCTIONS
*/

int			ft_parse_params(t_env *env, char **av);

/*
** CHAMP PARSING
*/

void		ft_parse_champs(t_env *env);

/*
** FREE FUNCTIONS
*/

void		ft_free_env(t_env *env);
void		ft_free_champs(t_env *env);
void		ft_free_champ(t_champ *champ);
void		ft_free_process(t_process *process);
/*
**	VISU FUNC
*/

void		ft_visu(t_env *env);
void		ft_run_once(t_env *env);
/*
** ARENA FUNC
*/

int			ft_init_arena(t_env *env);
int			ft_arena_error(int error);

/*
** PROCESS FUNC
*/

void		ft_get_process_infos(t_process *process, t_arena *arena);
int			ft_add_process(t_arena *arena, int pos);
int			ft_clone_process(t_arena *arena, t_process *to_clone, int pos);
void		ft_live(t_opcode *op, t_process *process, t_arena *arena);
void		ft_ld(t_opcode *op, t_process *process, t_arena *arena);
void		ft_st(t_opcode *op, t_process *process, t_arena *arena);
void		ft_add(t_opcode *op, t_process *process, t_arena *arena);
void		ft_sub(t_opcode *op, t_process *process, t_arena *arena);
void		ft_and(t_opcode *op, t_process *process, t_arena *arena);
void		ft_or(t_opcode *op, t_process *process, t_arena *arena);
void		ft_xor(t_opcode *op, t_process *process, t_arena *arena);
void		ft_zjmp(t_opcode *op, t_process *process, t_arena *arena);
void		ft_ldi(t_opcode *op, t_process *process, t_arena *arena);
void		ft_sti(t_opcode *op, t_process *process, t_arena *arena);
void		ft_fork(t_opcode *op, t_process *process, t_arena *arena);
void		ft_lld(t_opcode *op, t_process *process, t_arena *arena);
void		ft_lldi(t_opcode *op, t_process *process, t_arena *arena);
void		ft_lfork(t_opcode *op, t_process *process, t_arena *arena);
void		ft_aff(t_opcode *op, t_process *process, t_arena *arena);

void		ft_move_process(t_opcode *op, t_process *process, t_arena *arena);
void		ft_write_in_arena(t_arena *arena, int pos, int32_t value, int owner);
int32_t		ft_get_value_from_address(t_arena *arena, int pos, int offset);
int32_t		ft_get_value_from(t_opcode *op, t_process *process, t_arena *arena, int num);
int32_t		ft_parse_value(t_arena *arena, int pos, int size);

/*
** VERBOSE FUNC
*/

int			ft_verbose_flag(int flag);
void		ft_intro(t_env *env);
void		ft_verbose_cycles(t_env *env);
void		ft_verbose_dump_arena(t_arena *arena);
void		ft_verbose_move(t_opcode *op, t_process *process, t_arena *arena);
void		ft_verbose_op(t_arena *arena, t_process *process, t_opcode *opcode);

extern void 		(*op_func[17])(t_opcode*, t_process*, t_arena*);
#endif
