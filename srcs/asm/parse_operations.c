/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jates- <jates-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 12:23:55 by jates-            #+#    #+#             */
/*   Updated: 2019/12/30 12:23:56 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_check_str(t_file *file, t_token *tmp, int status)
{
	if (!tmp || tmp->type != STRING)
	{
		file->mode = CONTAIN_ERRORS;
		ft_printf("pas de string\n");
		return (0);
	}
	else if (status)
	{
		file->mode = CONTAIN_ERRORS;
		ft_printf("commande deja have\n");
		return (0);
	}
	else if (!tmp->next || tmp->next->type != NEWLINE)
	{
		file->mode = CONTAIN_ERRORS;
		ft_printf("problem syntax no newline\n");
		return (0);
	}
	else
	{
		file->tokens = tmp->next->next->next;
		return (1);
	}
}

int		ft_check_name(t_file *file)
{
	t_token		*tmp;
	static int	status = 0;

	if (!(tmp = file->tokens))
		return (0);
	if (tmp->type == COMMAND && ft_strnequ(tmp->value, NAME_CMD_STRING,\
	ft_strlen(NAME_CMD_STRING) + 1) && ft_check_str(file, tmp->next, status))
	{
		ft_memccpy(file->header.prog_name, tmp->next->value, '\0',\
			PROG_NAME_LENGTH + 1);
		free(tmp->next->next);
		free(tmp->next);
		free(tmp);
		if (file->header.prog_name[PROG_NAME_LENGTH])
		{
			ft_printf("name too long\n");
			file->mode = CONTAIN_ERRORS;
			return (0);
		}
		return (++status);
	}
	return (0);
}

int		ft_check_comment(t_file *file)
{
	t_token		*tmp;
	static int	status = 0;

	if (!(tmp = file->tokens))
		return (0);
	if (tmp->type == COMMAND && ft_strnequ(tmp->value, COMMENT_CMD_STRING,\
	ft_strlen(COMMENT_CMD_STRING) + 1)&& ft_check_str(file, tmp->next, status))
	{
		ft_memccpy(file->header.prog_name, tmp->next->value, '\0',\
				COMMENT_LENGTH + 1);
		file->tokens = tmp->next->next->next;
		free(tmp->next->next);
		free(tmp->next);
		free(tmp);
		if (file->header.prog_name[COMMENT_LENGTH])
		{
			ft_printf("comment too long\n");
			file->mode = CONTAIN_ERRORS;
			return (0);
		}
		return (++status);
	}
	return (0);
}

int ft_check_label(t_file *file)
{

}

int ft_check_op(t_file *file)
{

}