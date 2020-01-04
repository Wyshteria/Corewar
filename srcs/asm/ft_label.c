/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_label.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jates- <jates-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 09:09:54 by jates-            #+#    #+#             */
/*   Updated: 2020/01/04 09:12:50 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				ft_free_label(t_program *prog)
{
	t_label	*ptr;
	t_label	*tmp;

	ptr = prog->label;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
}

static t_label		*ft_is_in_label(t_program *prog, char *label)
{
	t_label *tmp;

	tmp = prog->label;
	while (tmp)
	{
		if (!ft_strnequ(label, tmp->value, ft_strlen(label) + 1))
			tmp = tmp->next;
		else
			return (tmp);
	}
	return (NULL);
}

int					ft_add_label(t_file *file, t_program *prog, char *label, t_token *token)
{
	t_label **tmp;

	tmp = &(prog->label);
	while (*tmp)
	{
		if (!ft_strnequ(label, (*tmp)->value, ft_strlen(label) + 1))
			tmp = &((*tmp)->next);
		else
		{
			ft_printf("At [%d:%d] ", token->line, token->col);
			ft_printf("label %s already used at [%d:%d]\n", label, (*tmp)->line, (*tmp)->col);
			file->mode = CONTAIN_ERRORS;
			return (0);
		}
	}
	if (!(*tmp = (t_label*)malloc(sizeof(t_label))))
		ft_crash(MALLOC_FAIL);
	ft_bzero(*tmp, sizeof(t_label));
	(*tmp)->value = label;
	(*tmp)->col = token->col;
	(*tmp)->line = token->line;
	(*tmp)->mem = prog->header.prog_size;
	return (1);
}

static void			ft_update_param_labels(t_program *prog)
{
	t_operation		*tmp;
	int				i;

	tmp = prog->operations;
	while (tmp)
	{
		i = -1;
		while (++i < tmp->p_num)
		{
			if (tmp->params[i].value_type == LABEL)
			{
					tmp->params[i].int_value = ft_is_in_label(prog, \
						tmp->params[i].value)->mem - tmp->mem;
			}
		}
		tmp = tmp->next;
	}
}

int					ft_check_labels(t_file *file, t_program *prog, \
	t_token *token)
{
	while (token)
	{
		if ((token->type == DIRECT_LABEL || token->type == INDIRECT_LABEL)
			&& !ft_is_in_label(prog, token->value))
		{
			ft_printf("label is not referenced\n");
			ft_syntax_error(file, token);
			return (0);
		}
		token = token->next;
	}
	ft_update_param_labels(prog);
	return (1);
}
