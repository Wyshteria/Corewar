/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jates- <jates-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 09:13:17 by jates-            #+#    #+#             */
/*   Updated: 2020/01/04 09:16:53 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	ft_param_len(int nbr_param, t_operation *operation, t_op const *op)
{
	if (operation->params[nbr_param].type == T_REG)
	{
		operation->encoding += REG_CODE << ((3 - nbr_param) * 2);
		operation->params[nbr_param].len = 1;
	}
	else if (operation->params[nbr_param].type == T_DIR)
	{
		operation->encoding += DIR_CODE << ((3 - nbr_param) * 2);
		operation->params[nbr_param].len = 4 - 2 * op->t_dir_is_two_bytes;
	}
	else if (operation->params[nbr_param].type == T_IND)
	{
		operation->encoding += IND_CODE << ((3 - nbr_param) * 2);
		operation->params[nbr_param].len = 2;
	}
	operation->len += operation->params[nbr_param].len;
}

static void	ft_param_init(t_token *token, int nbr_param, \
	t_operation *operation, t_op const *op)
{
	ft_bzero(&(operation->params[nbr_param]), sizeof(t_param));
	if (token->type == REGISTER)
		operation->params[nbr_param].type = T_REG;
	else if (token->type == DIRECT || token->type == DIRECT_LABEL)
		operation->params[nbr_param].type = T_DIR;
	else if (token->type == INDIRECT || token->type == INDIRECT_LABEL)
		operation->params[nbr_param].type = T_IND;
	operation->params[nbr_param].int_value = token->int_value;
	operation->params[nbr_param].value = token->value;
	if (token->type == DIRECT_LABEL || token->type == INDIRECT_LABEL)
		operation->params[nbr_param].value_type = LABEL;
	else if (token->type == DIRECT || token->type == INDIRECT)
		operation->params[nbr_param].value_type = NUMBER;
	else
		operation->params[nbr_param].value_type = token->type;
	ft_param_len(nbr_param, operation, op);
}

int			ft_create_param(t_file *file, t_operation *operation, \
	t_token **token, t_op const *op)
{
	int nbr_param;

	nbr_param = 0;
	*token = (*token)->next;
	while (*token)
	{
		if ((*token)->type == REGISTER || (*token)->type == DIRECT\
		|| (*token)->type == DIRECT_LABEL || (*token)->type == INDIRECT \
		|| (*token)->type == INDIRECT_LABEL)
			ft_param_init(*token, nbr_param, operation, op);
		else
			break ;
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

int			ft_check_params_types(t_file *file, t_operation *operation, \
		t_op const *op)
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
