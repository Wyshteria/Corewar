/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jates- <jates-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 00:52:11 by jates-            #+#    #+#             */
/*   Updated: 2019/12/19 03:09:31 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

size_t	ft_strspn(const char *s, const char *charset)
{
	size_t			i;
	const char *const	accept = charset;

	i = 0;
	while (*s)
	{
		while (*charset && (*s == *charset))
			charset++;
		if (*s != *charset)
			return (i);
		else
			charset = accept;
		s++;
		i++;
	}
	return (i);
}

int		ft_lexical_error(t_file *file, t_token *token)
{
	if (!token)
		ft_printf("Lexical error at [%d:%d]\n", file->line, file->col);
	else
		ft_printf("Lexical error at [%d:%d]\n", token->line, token->col);
	file->mode = CONTAIN_ERRORS;
	return (0);
}

int		ft_syntax_error(t_file *file, t_token *tok)
{
	char const	syntax[] = "Syntax error at token [TOKEN]";
	size_t		ret;

	if (!tok)
		ft_printf("%s[%03d:%03d] END \"(null)\"\n",\
	syntax, file->line, file->col + 1);
	else if (tok->type == NEWLINE)
		ft_printf("%s[%03d:%03d] ENDLINE\n",\
	syntax, tok->line, tok->col);
	else if (tok->type == COMMAND_NAME)
		ft_printf("%s[%03d:%03d] COMMAND_NAME \"%C%s\"\n",\
	syntax, tok->line, tok->col, CMD_CHAR, tok->value);
	else if (tok->type == COMMAND_COMMENT)
		ft_printf("%s[%03d:%03d] COMMAND_COMMENT \"%C%s\"\n",\
	syntax, tok->line, tok->col, CMD_CHAR, tok->value);
	else if (tok->type == COMMAND)
		return (ft_lexical_error(file, tok));
	else if (tok->type == LABEL)
		ft_printf("%s[%03d:%03d] LABEL \"%s%C\"\n", \
	syntax, tok->line, tok->col, tok->value, LABEL_CHAR);
	else if (tok->type == STRING)
		ft_printf("%s[%03d:%03d] STRING \"%C%s%C\"\n", \
	syntax, tok->line, tok->col, STRING_CHAR, tok->value, STRING_CHAR);
	else if (tok->type == DIRECT && !tok->next)
		return (ft_lexical_error(file, tok));
	else if (tok->type == DIRECT && tok->next->type == UNKNOWN \
		&& !(ret = ft_strspn(tok->next->value, "0123456789")))
		return (0);
	else if (tok->type == DIRECT && tok->next->type == NUMBER)
		ft_printf("%s[%03d:%03d] DIRECT \"%C%d\"\n", \
	syntax, tok->line, tok->col, DIRECT_CHAR, tok->value);
	file->mode = CONTAIN_ERRORS;
	return (0);

}
