/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 01:38:07 by toliver           #+#    #+#             */
/*   Updated: 2019/12/04 04:09:20 by toliver          ###   ########.fr       */
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

typedef struct		s_env
{
	char			*prog_name;
	int				ac;
	int				flags;
	size_t			dump_cycles;
	size_t			cycle_dump_cycles;
	int				verbose_level;
}					t_env;

#endif
