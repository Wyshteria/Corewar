#include "asm.h"

int		ft_pass_newline(t_file *file, t_token **token)
{
	t_token		*tmp;

	if (!*token)
		return(ft_syntax_error(file, *token));
	if ((*token)->type != NEWLINE)
		return (1);
	tmp = (*token)->next;
	while (tmp)
	{
		*token = tmp;
		if (tmp->type != NEWLINE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		ft_pass_comm(t_file *file, t_token **token)
{
	t_token		*tmp;

	if (!*token)
		return(ft_syntax_error(file, *token));
	if ((*token)->type != COMMENT)
		return (1);
	tmp = (*token)->next;
	while (tmp)
	{
		*token = tmp;
		if (tmp->type != COMMENT)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		ft_pass_newline_comm(t_file *file, t_token **token)
{
	t_token		*tmp;

	if (!*token)
		return(ft_syntax_error(file, *token));
	if ((*token)->type != NEWLINE && (*token)->type != COMMENT)
		return (1);
	tmp = (*token)->next;
	while (tmp)
	{
		*token = tmp;
		if (tmp->type != NEWLINE && tmp->type != COMMENT)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}