#include "asm.h"

t_operation	*ft_operation_init(t_program *prog, t_op *op)
{
	t_operation *tmp;
	t_operation *ptr;

	if (!(tmp = (t_operation*)malloc(sizeof(t_operation))))
		ft_crash(MALLOC_FAIL);
	ft_bzero(tmp, sizeof(t_operation));
	tmp->mem = prog->len;
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

void	ft_param_init(t_token *token, t_param *param)
{
	ft_bzero(param, sizeof(t_param));
	if (token->type == REGISTER)
		param->type = T_REG;
	else if (token->type == DIRECT || token->type == DIRECT_LABEL)
		param->type = T_DIR;
	else if (token->type == INDIRECT || token->type == INDIRECT_LABEL)
		param->type = T_IND;
	if (token->type != DIRECT_LABEL || token->type != INDIRECT_LABEL)
		param->int_value = token->int_value;
	param->value = token->value;
	if (token->type == DIRECT_LABEL || token->type == INDIRECT_LABEL)
		param->value_type = LABEL;
	else if (token->type == DIRECT || token->type == INDIRECT)
		param->value_type = NUMBER;
	else
		param->value_type = token->type;	
}

int		ft_create_param(t_file *file, t_operation *operation, t_token **token, t_op *op)
{
	int nbr_param;

	nbr_param = 0;
	*token = &((*token)->next);
	while (*token)
	{
		if ((*token)->type == REGISTER || (*token)->type == DIRECT\
		|| (*token)->type == DIRECT_LABEL || (*token)->type == INDIRECT \
		|| (*token)->type == INDIRECT_LABEL)
			ft_param_init(*token, &(operation->params[nbr_param]));
		else
			break;
		*token = &((*token)->next);
		if (*token && (*token)->type == SEPARATOR)
		{
			*token = &((*token)->next);
			if (++nbr_param == op->params_number)
			{
				ft_printf("too much param or separator\n");
				file->mode = CONTAIN_ERRORS;
				return (0);
			}
		}
	}
	return (1);
}

int		ft_check_params_types(t_file *file, t_operation *operation, t_op *op)
{
	int nbr_param;

	nbr_param = 0;
	while (nbr_param != op->params_number && operation->params[nbr_param].type)
	{
		if (!(op->params[nbr_param] & operation->params[nbr_param].type))
		{
			ft_printf("wrong param in the operation\n");
				file->mode = CONTAIN_ERRORS;
				return (0);
		}
		nbr_param++;
	}
	if (nbr_param != op->params_number)
	{
		ft_printf("not enough param in the op %s\n", operation->name);
		file->mode = CONTAIN_ERRORS;
		return (0);
	}
	return (1);
}

char	*ft_type_param(t_param *param)
{
	if (param->type == T_DIR)
		return ("T_DIR");
	else if (param->type == T_IND)
		return ("T_IND");
	else if (param->type == T_REG)
		return ("T_REG");
	else
		return ("UNKNOWN");	
}

void		ft_dump_op(t_program *prog)
{
	t_operation *ptr;
	int			i;

	ptr = prog->operations;
	while (ptr)
	{
		ft_printf("operation name = %s\n", ptr->name);
		ft_printf("\topc = %d\n", ptr->opc);
		ft_printf("\tmemory address = %d\n", ptr->memory);
		ft_printf("\tlength = %d\n", ptr->len);
		ft_printf("\tparam_number [%d]\n", ptr->p_num);
		i = -1;
		while (++i < 3)
		{
			ft_printf("\t\tparam[%d] = %s\n", i + 1, ptr->params[i].value);
			ft_printf("\t\t\ttype = %s\n", ft_type_param(&ptr->params[i]));
			ft_printf("\t\t\tint_val %d\n", ptr->params[i].int_value);
			ft_printf("\t\t\tvalue_type %s\n\n", ft_tokentype_string(ptr->params[i].value_type));
		}
		ptr = ptr->next;
	}
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