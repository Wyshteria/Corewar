/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jates- <jates-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 09:22:46 by jates-            #+#    #+#             */
/*   Updated: 2020/01/04 09:27:45 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_operation	*ft_op_init(t_program *prog, t_op const *op, t_token *token)
{
	t_operation *tmp;
	t_operation *ptr;

	if (!(tmp = (t_operation*)malloc(sizeof(t_operation))))
		ft_crash(MALLOC_FAIL);
	*tmp = (t_operation) {.mem = prog->header.prog_size, \
	.opc = op->opcode_value, .name = op->opcode, .encoding = 0, \
	.prev = NULL, .next = NULL, \
	.p_num = op->params_number, .line = token->line,\
	.len = op->need_encoding_byte + 1, .col = token->line, \
	.is_encoding_needed = op->need_encoding_byte, .params[0] = {0}, \
	.params[1] = {0}, .params[2] = {0}};
	if (prog->operations == NULL)
		prog->operations = tmp;
	else
	{
		ptr = prog->operations;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = tmp;
	}
	return (tmp);
}

int					ft_check_op(t_file *file, t_program *prog, t_token **token)
{
	t_op *const	op = ft_fetch_op((*token)->value);
	t_operation	*operation;

	operation = ft_op_init(prog, op, *token);
	if (!ft_create_param(file, operation, token, op))
		return (0);
	ft_pass_comm(file, token);
	if (!*token || (*token)->type != NEWLINE)
	{
		ft_printf("At [%d:%d] the ", operation->line, operation->col);
		ft_printf("operation does not end with a newline\n");
		return (ft_syntax_error(file, *token));
	}
	if (!ft_check_params_types(file, operation, op))
		return (0);
	prog->header.prog_size += operation->len;
	return (1);
}

void				ft_free_op(t_program *prog)
{
	t_operation	*ptr;
	t_operation	*tmp;

	ptr = prog->operations;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
	prog->operations = NULL;
}
