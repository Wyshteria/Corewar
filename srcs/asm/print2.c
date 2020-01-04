/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:58:03 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 09:42:59 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*ft_tokentype_string2(int type)
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
	else
		return ("UNKNOWN");
}

char		*ft_tokentype_string(int type)
{
	if (type == SEPARATOR)
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
		return (ft_tokentype_string2(type));
}

void		ft_dump_param(t_operation *ptr)
{
	int			i;

	i = -1;
	while (++i < 3)
	{
		ft_printf("\t\t\t\tparam[%d] = %s\n", i + 1, ptr->params[i].value);
		ft_printf("\t\t\t\t\ttype = %s\n", ft_type_param(&ptr->params[i]));
		ft_printf("\t\t\t\t\tint_val %d\n", ptr->params[i].int_value);
		ft_printf("\t\t\t\t\tvalue_type %s\n\n", \
			ft_tokentype_string(ptr->params[i].value_type));
		ft_printf("\t\t\t\t\tlength %d\n", ptr->params[i].len);
	}
}

void		ft_dump_op(t_program *prog)
{
	t_operation	*ptr;

	ptr = prog->operations;
	while (ptr)
	{
		ft_printf("\t\toperation name = %s\n", ptr->name);
		ft_printf("\t\t\topc = %d\n", ptr->opc);
		ft_printf("\t\t\tmemory address = %d\n", ptr->mem);
		ft_printf("\t\t\tlength = %d\n", ptr->len);
		ft_printf("\t\t\t%d encoding [%#x]\n",\
			ptr->is_encoding_needed, ptr->encoding);
		ft_printf("\t\t\tparam_number [%d]\n", ptr->p_num);
		ft_dump_param(ptr);
		ptr = ptr->next;
	}
}

void		ft_dump_prog(t_program *prog)
{
	ft_printf("file name : %s\n", prog->filename);
	ft_printf("\tHeader\n\t\tmagic = %u\n", prog->header.magic);
	ft_printf("\t\tprog_name = %.*s\n", PROG_NAME_LENGTH + 1,\
		prog->header.prog_name);
	ft_printf("\t\tcomment = %.*s\n", COMMENT_LENGTH + 1,\
		prog->header.comment);
	ft_printf("\t\tprog_size = %u\n", prog->header.prog_size);
	ft_printf("\n");
	ft_printf("\tfd [%d]\n", prog->fd);
	ft_printf("\tLabels :\n");
	ft_dump_label(prog);
	ft_printf("\tOperations :\n");
	ft_dump_op(prog);
}
