#include "asm.h"

char		*ft_type_param(t_param *param)
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

static void	ft_param_init(t_token *token, t_param *param)
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

int			ft_create_param(t_file *file, t_operation *operation, t_token **token, t_op *op)
{
	int nbr_param;

	nbr_param = 0;
	*token = (*token)->next;
	while (*token)
	{
		if ((*token)->type == REGISTER || (*token)->type == DIRECT\
		|| (*token)->type == DIRECT_LABEL || (*token)->type == INDIRECT \
		|| (*token)->type == INDIRECT_LABEL)
			ft_param_init(*token, &(operation->params[nbr_param]));
		else
			break;
		*token = (*token)->next;
		if (*token && (*token)->type == SEPARATOR)
		{
			*token = (*token)->next;
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

int			ft_check_params_types(t_file *file, t_operation *operation, t_op *op)
{
	int nbr_param;

	nbr_param = 0;
	// ft_printf("check_params_types\n");
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

