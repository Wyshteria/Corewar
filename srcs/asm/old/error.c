/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:24:24 by toliver           #+#    #+#             */
/*   Updated: 2019/11/24 16:28:50 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	else if (error == MISSING_NAME || error == MISSING_COMMENT)
	{
		ft_dprintf(2, "%s: %s: missing '%s' before instructions\n", env->prog_name, file->filename, error == MISSING_NAME ? ".name" : ".comment");
	}
	else
		ft_dprintf(2, "unknown error !\n");
	return (0);
}

int			ft_error(t_env *env, t_file *file, int error)
{
	env->mode = ERROR;
	env->error.value = error;
	ft_dprintf(2, "%s: %s: %s\n", env->prog_name, file->filename, strerror(errno));
	return (0);
}

int			ft_crash(t_env *env, int error)
{
	env->mode = CRASH;
	env->error.value = error;
	return (0);
}
