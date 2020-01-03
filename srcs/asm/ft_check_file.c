/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jates- <jates-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 03:31:42 by jates-            #+#    #+#             */
/*   Updated: 2020/01/02 03:31:44 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_check_header(t_file *file)
{
	t_token		*tmp;
	int			cmd;

	cmd = 0;
	while (cmd != 2)
	{
		tmp = file->tokens;
		if (!ft_pass_newline(file, &tmp))
			return (0);
		if (tmp && tmp->prev)
		{
			tmp->prev->next = NULL;
			ft_free_file(file);
			tmp->prev = NULL;
			file->tokens = tmp;
		}
		if (ft_check_comment(file))
			cmd++;
		else if (ft_check_name(file))
			cmd++;
		else
			return (0);
	}
	return (1);
}

int		ft_add_label(t_file *file, t_program *prog, char *label)
{
	t_label **tmp;

	tmp = &(file->label);
	while (*tmp)
	{
		if (!ft_strnequ(label, (*tmp)->value, ft_strlen(label) + 1))
			tmp = &((*tmp)->next);
		else
		{
			ft_printf("label %s already used\n", label);
			file->mode = CONTAIN_ERRORS;
			return (0);
		}
	}
	if (!(*tmp = (t_label*)malloc(sizeof(t_label))))
		ft_crash(MALLOC_FAIL);
	(*tmp)->value = label;
	(*tmp)->next = NULL;
	(*tmp)->mem = prog->len;
	return (1);
}

t_token		*ft_check_body(t_file *file, t_program *prog)
{
	t_token			*tmp;
	
	tmp = file->tokens;
	while (tmp)
	{
		if (!ft_pass_newline_comm(file, &tmp))
			return (NULL);
		if (tmp->type == LABEL && (!tmp->next || (tmp->next != NEWLINE_CHAR \
		&& tmp->next != OPERATION && tmp->next != COMMENT))
			return (ft_syntax_error(file, tmp));
		else if (tmp->type == LABEL && !ft_add_label(file, prog, tmp->value))
			return (0);
		else if (tmp->type == OPERATION && !ft_check_op(file, prog, tmp))
		{
				ft_dump_op(prog);
				ft_free_op(prog);
				return (0);
		}
	}
}

t_label		*ft_is_in_label(t_file *file, char *label)
{
	t_label *tmp;

	tmp = file->label;
	while (tmp)
	{
		if (!ft_strnequ(label, tmp->value, ft_strlen(label) + 1))
			tmp = tmp->next;
		else
			return (tmp);
	}
	return (NULL);
}

int			ft_check_labels(t_file *file, t_token *token)
{
	while (token)
	{
		if ((token->type == DIRECT_LABEL || token->type == INDIRECT_LABEL) 
			&& !ft_is_in_label(file, token->value))
			{
				ft_printf("label is not referenced\n");
				ft_syntax_error(file, token);
				return (0);
			}
		token = token->next;
	}
	return (1);
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

int		ft_check_operation(t_file *file, t_program *prog)
{
	t_token *token;

	token = file->tokens;
	while (token)
	{
		if (token->type == OPERATION)
		{
			if (!ft_check_op(file, prog, token))
			{
				ft_dump_op(prog);
				ft_free_op(prog);
				return (0);
			}
		}
		token = token->next;
	}
	ft_dump_op(prog);
	ft_free_op(prog);
	return (0);
	return (1);
}