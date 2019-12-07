/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 01:38:07 by toliver           #+#    #+#             */
/*   Updated: 2019/12/07 19:50:30 by toliver          ###   ########.fr       */
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

#define CONCATABLE_FLAGS "a"
#define PARAMS_FLAGS "dsv"

#define AFF_FLAG 0x1 // a
#define DUMP_FLAG 0x2 // d
#define CYCLE_DUMP_FLAG 0x4 // s
#define VERBOSE_FLAG 0x8 // v

#define VERBOSE_LIVES_FLAG 0x1
#define VERBOSE_CYCLES_FLAG 0x2
#define VERBOSE_OPERATIONS_FLAG 0x4
#define VERBOSE_DEATH_FLAG 0x8
#define VERBOSE_PC_MOVEMENT_FLAG 0x16

enum				e_parsing_modes
{
	PARSE_FLAGS,
	PARSE_FILES,
	PARSE_ERROR,
	PARSE_CRASH
};

enum				e_parsing_errors
{
	UNKNOWN_FLAG,
	PARAM_FLAG_WRONG,
	PARAM_MISSING,
	PARAM_NEGATIVE,
};

enum				e_champ_error
{
	OPEN_ERROR,
	READ_ERROR,
	MAGIC_ERROR,
	TOO_SHORT,
	NAME_TOO_LONG,
	COMMENT_TOO_LONG,
	SIZE_ERROR,
};

typedef struct		s_champ
{
	t_header		header;
	int				fd;
	int				offset;
	char			*filename;
	char			*content;
	struct s_champ	*next;
}					t_champ;

typedef struct		s_env
{
	char			*prog_name;
	int				ac;
	int				flags;
	size_t			dump_cycles;
	size_t			cycle_dump_cycles;
	int				verbose_level;
	t_champ			*champs;
}					t_env;

/*
** DUMP FUNCTIONS
*/

void		ft_dump_env(t_env *env);
void		ft_dump_champs(t_env *env);
void		ft_dump_header(t_header *header);
void		ft_dump_flags(t_env *env);
void		ft_dump_verbose_flags(t_env *env);

/*
** UTILS FUNCTIONS
*/

uint32_t	ft_swap(uint32_t toswap);
int			ft_is_containing_other_than(char *str, char *containing);
int			ft_pow2(int pow);
int			ft_strchr_pos(char *str, int c);
int			ft_is_one_of(char c, char *lookfor);
void		*ft_malloc(size_t size);

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
** FREE FUNCTIONS
*/

void		ft_free_env(t_env *env);
void		ft_free_champs(t_env *env);
void		ft_free_champ(t_champ *champ);

#endif
