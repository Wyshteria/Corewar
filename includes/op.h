/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jates- <jates-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2020/02/24 17:26:18 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H
# include <stdint.h>

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE/8)
# define CHAMP_MAX_SIZE			(MEM_SIZE/6)

# define COMMENT_CHAR			'#'
# define ALT_COMMENT_CHAR		';'
# define CMD_CHAR				'.'
# define STRING_CHAR			'"'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','
# define NEWLINE_CHAR			'\n'

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		"name"
# define COMMENT_CMD_STRING		"comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct			s_header
{
	uint32_t			magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	uint32_t			prog_size;
	char				comment[COMMENT_LENGTH + 1];
}						t_header;

typedef struct			s_op
{
	char				*opcode;
	unsigned char		params_number;
	unsigned char		params[REG_NUMBER];
	unsigned char		opcode_value;
	unsigned int		cycles;
	char				*opcode_name;
	int					need_encoding_byte;
	int					t_dir_is_two_bytes;
}						t_op;

extern t_op				g_op_tab[17];
#endif
