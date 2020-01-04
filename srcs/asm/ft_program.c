/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_program.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jates- <jates-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 09:05:10 by jates-            #+#    #+#             */
/*   Updated: 2020/01/04 09:09:20 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char			*ft_cor_filename(t_file *file)
{
	const int	len = ft_strlen(file->filename);
	char		*corname;

	corname = NULL;
	if (len > 2 && file->filename[len - 2] == '.'
	&& file->filename[len - 1] == 's' && file->filename[len] == 0)
	{
		if ((corname = ft_strnew(len + 2)) \
		&& ft_strncpy(corname, file->filename, len - 1))
			return (ft_strcat(corname, "cor"));
		ft_crash(MALLOC_FAIL);
	}
	else
	{
		if ((corname = ft_strnew(len + 4)) \
		&& ft_strncpy(corname, file->filename, len))
			return (ft_strcat(corname, ".cor"));
		ft_crash(MALLOC_FAIL);
	}
	return (corname);
}

static int			ft_check_body(t_file *file, t_program *prog)
{
	t_token			*tmp;

	tmp = file->tokens;
	while (tmp)
	{
		if (!ft_pass_newline_comm(file, &tmp))
			return (file->mode != CONTAIN_ERRORS);
		if (tmp->type == LABEL && (!tmp->next || (tmp->next->type != NEWLINE \
		&& tmp->next->type != OPERATION && tmp->next->type != COMMENT)))
			return (ft_syntax_error(file, tmp));
		else if (tmp->type == LABEL)
		{
			if (!ft_add_label(file, prog, tmp->value))
				return (0);
		}
		else if (tmp->type == OPERATION)
		{
			if (!ft_check_op(file, prog, &tmp))
				return (0);
		}
		else
			return (ft_syntax_error(file, tmp));
		tmp = tmp->next;
	}
	return (1);
}

int					ft_init_prog(t_env *env, t_file *file)
{
	ft_clear_prog(&env->prog);
	env->prog.header.magic = COREWAR_EXEC_MAGIC;
	if (!(env->prog.filename = ft_cor_filename(file)))
		return (0);
	ft_printf("got the name\n");
	if (!ft_check_header(file, &env->prog) || !ft_check_body(file, &env->prog) \
	|| !ft_check_labels(file, &env->prog, file->tokens))
	{
		ft_clear_prog(&env->prog);
		return (0);
	}
	return (1);
}

void				ft_clear_prog(t_program *prog)
{
	ft_free_op(prog);
	ft_free_label(prog);
	free(prog->filename);
	ft_bzero(prog, sizeof(t_program));
}
