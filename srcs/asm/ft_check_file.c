#include "asm.h"

t_token	*ft_check_header(t_file *file)
{
	t_token		*tmp;
	int			cmd;

	tmp = file->tokens;
	if (!ft_pass_newline(file, &tmp))
		return (NULL);
	cmd = 0;
	while (tmp->type < STRING)
	{
		if (tmp->type > COMMAND)
			cmd++;
		tmp = tmp->next;
		if (!tmp || tmp->type != STRING)
			return (NULL);
		tmp = tmp->next;
		if (!tmp || tmp->type != NEWLINE)
			return (NULL);
		if (!ft_pass_newline(file, &tmp))
			return (NULL);
	}
	if (cmd != 2)
		return (NULL);
	if (file->header.prog_name[PROG_NAME_LENGTH])
	{
		ft_printf("name too long\n");
		file->mode = CONTAIN_ERRORS;
		return (NULL);
	}
	else if (file->header.comment[COMMENT_LENGTH])
	{
		ft_printf("commentaire too long\n");
		file->mode = CONTAIN_ERRORS;
		return (NULL);
	}
	tmp->prev->next = NULL;
	ft_free_file(file);
	file->tokens = tmp;
	return (tmp);
}

int ft_is_in_label(t_file *file, char *label)
{
	t_label *tmp;

	tmp = file->label;
	while (tmp)
	{
		if (!ft_strnequ(label, tmp->value, ft_strlen(label) + 1))
			tmp = tmp->next;
		else
			return (1);
	}
	ft_printf("label %s not defined used\n", label);
	file->mode = CONTAIN_ERRORS;
	return (0);
}

int ft_check_labels(t_file *file, t_token *token)
{
	while (token)
	{
		if (token->type == LABEL && !ft_is_in_label(file, token->value))
			return (0);
		token = token->next;
	}
	return (1);
}