/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:18:38 by toliver           #+#    #+#             */
/*   Updated: 2019/11/23 17:44:44 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/errno.h>
#include <fcntl.h>
#include "libft.h"
#include "libftprintf.h"
#include "op.h"

#define FLAGS ""


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

typedef struct		s_env
{
	char			*prog_name;
	int				mode;
	t_error			error;
	int				flags;
}					t_env;

typedef struct		s_file
{
	char			*filename; // do not free, is given the av value
	int				fd;
	off_t			offset;
	size_t			line;
	size_t			column;
	char			*name;
	char			*comment;
	void			*instructions;
}					t_file;
