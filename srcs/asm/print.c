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
	else if (type == COMMAND_NAME)
		return ("COMMAND_NAME");
	else if (type == COMMAND_COMMENT)
		return ("COMMAND_COMMENT");
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
	else if (type == DIRECT_LABEL)
		return ("DIRECT_LABEL");
	else if (type == INDIRECT)
		return ("INDIRECT");
	else if (type == INDIRECT_LABEL)
		return ("INDIRECT_LABEL");
	else if (type == NUMBER)
		return ("NUMBER");
	else if (type == INSTRUCTION)
		return ("INSTRUCTION");
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
** There is a segfault with %b for 0
*/

void		ft_dump_env(t_env *env)
{
	ft_printf("prog name : %s\n", env->prog_name);
	if (env->flags)
		ft_printf("prog flags = %b\n", env->flags);
	ft_dump_files(env->files);
}

void		ft_dump_op(t_program *prog)
{
	t_operation *ptr;
	int			i;

	ptr = prog->operations;
	while (ptr)
	{
		ft_printf("\toperation name = %s\n", ptr->name);
		ft_printf("\t\topc = %d\n", ptr->opc);
		ft_printf("\t\tmemory address = %d\n", ptr->mem);
		ft_printf("\t\tlength = %d\n", ptr->len);
		ft_printf("\t\tparam_number [%d]\n", ptr->p_num);
		i = -1;
		while (++i < 3)
		{
			ft_printf("\t\t\tparam[%d] = %s\n", i + 1, ptr->params[i].value);
			ft_printf("\t\t\t\ttype = %s\n", ft_type_param(&ptr->params[i]));
			ft_printf("\t\t\t\tint_val %d\n", ptr->params[i].int_value);
			ft_printf("\t\t\t\tvalue_type %s\n\n", ft_tokentype_string(ptr->params[i].value_type));
		}
		ptr = ptr->next;
	}
}

void		ft_dump_prog(t_program *prog)
{
	ft_printf("file name : %s\n", prog->filename);
	ft_printf("\tHeader\n\t\tmagic = %u\n", prog->header.magic);
	ft_printf("\t\tprog_name = %.*s\n", PROG_NAME_LENGTH + 1, prog->header.prog_name);
	ft_printf("\t\tcomment = %.*s\n", COMMENT_LENGTH + 1, prog->header.comment);
	ft_printf("\t\tprog_size = %u\n", prog->header.prog_size);
	ft_printf("\n");
	ft_printf("\tfd [%d]\n", prog->fd);
	ft_printf("\tLabels :\n");
	ft_dump_label(prog);
	ft_printf("\tOperations :\n");
	ft_dump_op(prog);
}