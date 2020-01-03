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

int			ft_check_body(t_file *file, t_program *prog)
{
	t_token			*tmp;
	
	tmp = file->tokens;
	while (tmp)
	{
		if (!ft_pass_newline_comm(file, &tmp))
			return (0);
		if (tmp->type == LABEL && (!tmp->next || (tmp->next->type != NEWLINE_CHAR \
		&& tmp->next->type != OPERATION && tmp->next->type != COMMENT)))
			return (ft_syntax_error(file, tmp));
		else if (tmp->type == LABEL && !ft_add_label(file, prog, tmp->value))
			return (0);
		else if (tmp->type == OPERATION && !ft_check_op(file, prog, &tmp))
		{
				ft_dump_op(prog);
				ft_free_op(prog);
				return (0);
		}
	}
	return (1);
}
