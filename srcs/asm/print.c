/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:58:03 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 09:37:24 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_dump_tokens(t_file *file)
{
	t_token	*token;

	token = file->tokens;
	while (token)
	{
		ft_printf("token of type : %s\n", ft_tokentype_string(token->type));
		ft_printf("\tits value is : %s\n", token->value);
		ft_printf("\tits converted value is : %d\n", token->int_value);
		ft_printf("\tat pos [%d:%d]\n", token->line, token->col);
		token = token->next;
	}
}

void		ft_dump_label(t_program *prog)
{
	t_label *label;

	label = prog->label;
	while (label)
	{
		ft_printf("\t\t[%s]\tmem >%d<\n", label->value, label->mem);
		label = label->next;
	}
}

void		ft_dump_file(t_file *file)
{
	ft_printf("\tfile name = %s\n", file->filename);
	ft_printf("\tfile fd = %d\n", file->fd);
	ft_printf("\tline:col [%d:%d]\n", file->line, file->col);
	ft_printf("\tfile offset = %zu\n", file->offset);
	ft_printf("\tfile mode = %d\n", file->mode);
}

void		ft_dump_files(t_file *files)
{
	t_file	*ptr;

	ptr = files;
	while (ptr)
	{
		ft_dump_file(ptr);
		ptr = ptr->next;
	}
}

/*
** There is a segfault with %b for 0 if it s a char
*/

void		ft_dump_env(t_env *env)
{
	ft_printf("prog name : %s\n", env->prog_name);
	if (env->flags)
		ft_printf("prog flags = %b\n", env->flags);
	ft_dump_files(env->files);
}
