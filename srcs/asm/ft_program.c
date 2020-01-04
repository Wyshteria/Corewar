#include "asm.h"

static char	*ft_cor_filename(t_file *file)
{
	const int	len = ft_strlen(file->filename);
	char		*corname;

	corname = NULL;
	if (len > 2 && file->filename[len - 2] == '.'
	&& file->filename[len - 1] == 's' && file->filename[len] == 0)
	{
		if ((corname = ft_strnew(len + 2)) \
		&& ft_strncpy(corname, file->filename, len - 1))
			return(ft_strcat(corname, "cor"));
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


static int	ft_check_body(t_file *file, t_program *prog)
{
	t_token			*tmp;
	
	tmp = file->tokens;
	ft_printf("check the body\n");
	while (tmp)
	{
		if (!ft_pass_newline_comm(file, &tmp))
			return (0);
		if (tmp)
			{
				ft_printf("in printf de check_body\n");
				ft_printf("token of type : %s\n", ft_tokentype_string((tmp)->type));
				ft_printf("\tits value is : %s\n", (tmp)->value);
				ft_printf("\tits converted value is : %d\n", (tmp)->int_value);
				ft_printf("\tat pos [%d:%d]\n", (tmp)->line, (tmp)->col);
			}
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
			{
				// ft_printf("check op did not work\n");
				// ft_dump_op(prog);
				ft_free_op(prog);
				return (0);
			}
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
	if (!(env->prog.filename = ft_cor_filename(file)))
		return (0);
	ft_printf("got the name\n");
	ft_dump_tokens(file);
	if (!ft_check_header(file, &env->prog) || !ft_check_body(file,&env->prog) \
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