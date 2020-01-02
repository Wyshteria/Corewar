#include "asm.h"



t_operation	*ft_operation_init(t_program *prog, t_op *op)
{
	t_operation *tmp;
	t_operation *ptr;

	if (!(tmp = (t_operation*)malloc(sizeof(t_operation))))
		ft_crash(MALLOC_FAIL);
	ft_bzero(tmp, sizeof(t_operation));
	tmp->memory = prog->len;
	tmp->opc = op->opcode_value;
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

void	ft_init_param(t_program *prog, t_token *token, t_param *param, t_op *op)
{
	if (token->type == REGISTER)
			param->type = T_REG;
	else if (token->type == DIRECT || token->type == DIRECT_LABEL)
		param->type = T_DIR;
	else if (token->type == INDIRECT || token->type == INDIRECT_LABEL)
		param->type = T_IND;
	if (token->type == DIRECT_LABEL || token->type == INDIRECT_LABEL)
		param->value = token->value;
}

int		ft_create_param(t_file *file, t_operation *operation, t_token *token, t_op *op)
{
	int nbr_param;

	nbr_param = 0;
	token = token->next;
	while (token)
	{
		if (token->type == REGISTER)
			operation->params[nbr_param].type = T_REG;
		else if (token->type == DIRECT || token->type == DIRECT_LABEL)
			operation->params[nbr_param].type = T_DIR;
		else if (token->type == INDIRECT || token->type == INDIRECT_LABEL)
			operation->params[nbr_param].type = T_IND;
		else
			break;
		token = token->next;
		if (token && token->type == SEPARATOR)
		{
			token = token->next;
			if (++nbr_param == op->params_number)
			{
				ft_printf("too much params for operation\n");
				file->mode = CONTAIN_ERRORS;
				return (0);
			}
		}
	}
	return (1);
}

int		ft_check_operation(t_file *file, t_program *prog, t_token *token)
{
	t_op		*const op = ft_fetch(token->value);
	t_operation	*operation;

	operation = ft_operation_init(prog, op);

}

int		ft_param_init(t_operation *op, t_token *token, int number)
{
	if (token)



		// op->params[number]->type = 0 ;

}