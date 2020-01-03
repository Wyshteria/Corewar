#include "asm.h"

static t_operation	*ft_op_init(t_program *prog, t_op *op)
{
	t_operation *tmp;
	t_operation *ptr;

	if (!(tmp = (t_operation*)malloc(sizeof(t_operation))))
		ft_crash(MALLOC_FAIL);
	ft_bzero(tmp, sizeof(t_operation));
	tmp->mem = prog->header.prog_size;
	tmp->opc = op->opcode_value;
	tmp->name = op->opcode;
	tmp->p_num = op->params_number;
	tmp->len = op->carry + 1;
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

int		ft_check_op(t_file *file, t_program *prog, t_token **token)
{
	t_op		*const op = ft_fetch_op((*token)->value);
	t_operation	*operation;

	operation = ft_operation_init(prog, op);
	if (!ft_create_param(file, operation, token, op))
		return (0);
	if (!ft_pass_comm(file, token) || !*token || (*token)->type != NEWLINE)
	{
		ft_printf("operation does not end with a newline\n");
		file->mode = CONTAIN_ERRORS;
		return (0);
	}
	if (!ft_check_params_types(file, operation, op))
		return (0);
	return (1);
}

void	ft_free_op(t_program *prog)
{
	t_operation *ptr;
	t_operation *tmp;

	ptr = prog->operations;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
}

