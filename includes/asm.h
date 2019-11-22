/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:18:38 by toliver           #+#    #+#             */
/*   Updated: 2019/11/22 01:58:25 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/errno.h>
#include <fcntl.h>
#include "libft.h"
#include "libftprintf.h"


#define FLAGS "a"


enum mode 
{
	CRASH,
	ERROR,
	PARSING_ARGS,
	PARSING_FLAGS,
	PARSING_FILES,
	PARSING_OPENFILE,
	PARSING_FIRSTLINES,
	PARSING_NAME,
	PARSING_COMMENT,
	PARSING_INSTRUCTIONS,
	PARSING_DONE,
	FINISHED
};

enum error
{
	NO_PARAMS,
	WRONG_FLAGS,
	OPEN_ERROR,
	READ_ERROR,
	LSEEK_ERROR,
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
