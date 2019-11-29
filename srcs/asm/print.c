/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:58:03 by toliver           #+#    #+#             */
/*   Updated: 2019/11/29 16:00:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*ft_tokentype_string(int type)
{
	if (type == COMMAND)
		return ("COMMAND");
	else if (type == STRING)
		return ("STRING");
	else if (type == COMMENT)
		return ("COMMENT");
	else if (type == LABEL)
		return ("LABEL");
	else if (type == OPERATION)
		return ("OPERATION");
	else if (type == PARAM)
		return ("PARAM");
	else if (type == NEWLINE)
		return ("NEWLINE");
	else if (type == SEPARATOR)
		return ("SEPARATOR");
	else if (type == REGISTER)
		return ("REGISTER");
	else if (type == DIRECT)
		return ("DIRECT");
	else if (type == NUMBER)
		return ("NUMBER");
	else
		return ("UNKNOWN");
}

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

void		ft_dump_file(t_file *file)
{
	ft_printf("\tfile name = %s\n", file->filename);
	ft_printf("\tfile fd = %d\n", file->fd);
	ft_printf("\tline:col [%d:%d]\n", file->line, file->col);
	ft_printf("\tfile offset = %zu\n", file->offset);
	ft_printf("\t file mode = %d\n", file->mode);
	ft_printf("\n");
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

void		ft_dump_env(t_env *env)
{
	ft_printf("prog name : %s\n", env->prog_name);
	ft_printf("prog flags = %b\n", env->flags);
	ft_dump_files(env->files);
}
