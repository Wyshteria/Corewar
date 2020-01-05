/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jates- <jates-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 09:17:19 by jates-            #+#    #+#             */
/*   Updated: 2020/01/04 09:18:35 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		ft_free_head_token(t_file *file, t_token *tmp)
{
	if (tmp && tmp->prev)
	{
		tmp->prev->next = NULL;
		ft_free_file(file);
		tmp->prev = NULL;
		file->tokens = tmp;
	}
}

static int		ft_check_str(t_file *file, t_token *tmp, int status)
{
	if (!tmp->next || tmp->next->type != STRING)
	{
		ft_printf("no string for %s\n", tmp->value);
		return (ft_syntax_error(file, tmp));
	}
	else if (status)
	{
		ft_printf("Command %s already have\n", tmp->value);
		return (ft_syntax_error(file, tmp));
	}
	else if (!tmp->next->next || tmp->next->next->type != NEWLINE)
	{
		ft_printf("No newline\n");
		return (ft_syntax_error(file, tmp->next));
	}
	else
		return (1);
}

static int		ft_check_name(t_file *file, t_program *prog, int to_reinit)
{
	t_token		*tmp;
	static int	status = 0;

	if (to_reinit)
		return ((status = 0));
	if (!(tmp = file->tokens))
		return (0);
	if (tmp->type == COMMAND && ft_strnequ(tmp->value, NAME_CMD_STRING,\
	ft_strlen(NAME_CMD_STRING) + 1) && ft_check_str(file, tmp, status))
	{
		ft_memccpy(prog->header.prog_name, tmp->next->value, '\0',\
			PROG_NAME_LENGTH + 1);
		ft_free_head_token(file, tmp->next->next);
		if (prog->header.prog_name[PROG_NAME_LENGTH])
		{
			ft_printf("Name too long\n");
			return (ft_lexical_error(file, tmp));
		}
		return (++status);
	}
	return (0);
}

static int		ft_check_comment(t_file *file, t_program *prog, int to_reinit)
{
	t_token		*tmp;
	static int	status = 0;

	if (to_reinit)
		return ((status = 0));
	if (!(tmp = file->tokens))
		return (0);
	if (tmp->type == COMMAND && ft_strnequ(tmp->value, COMMENT_CMD_STRING,\
	ft_strlen(COMMENT_CMD_STRING) + 1) && ft_check_str(file, tmp, status))
	{
		ft_memccpy(prog->header.comment, tmp->next->value, '\0',\
				COMMENT_LENGTH + 1);
		ft_free_head_token(file, tmp->next->next);
		if (prog->header.comment[COMMENT_LENGTH])
		{
			ft_printf("Comment too long\n");
			return (ft_lexical_error(file, tmp));
		}
		return (++status);
	}
	return (0);
}

int				ft_check_header(t_file *file, t_program *prog)
{
	t_token		*tmp;
	int			cmd;

	cmd = 0;
	while (cmd != 2)
	{
		tmp = file->tokens;
		if (!ft_pass_newline(file, &tmp))
			return (0);
		ft_free_head_token(file, tmp);
		if (ft_check_comment(file, prog, 0))
			cmd++;
		else if (ft_check_name(file, prog, 0))
			cmd++;
		else
			return (0);
	}
	ft_check_comment(file, prog, 1);
	ft_check_name(file, prog, 1);
	return (1);
}
