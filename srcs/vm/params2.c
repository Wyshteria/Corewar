/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jates- <jates-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 04:15:49 by toliver           #+#    #+#             */
/*   Updated: 2020/02/24 17:23:12 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_add_champ(t_env *env, t_champ *champ)
{
	t_champ	*ptr;

	if (env->champs == NULL)
		env->champs = champ;
	else
	{
		ptr = env->champs;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = champ;
	}
}

void		ft_same_number_error(t_env *env, int number)
{
	ft_dprintf(2, "%s: Champion cannot have the same number %d\n",
			env->prog_name, number);
}

int			ft_parse_file1(t_env *env, t_champ *champ)
{
	t_champ	*node;

	if (!(node = (t_champ*)ft_safe_malloc(sizeof(t_champ))))
	{
		ft_dprintf(2, "%s: Malloc failed: %s\n",
				env->prog_name, strerror(errno));
		return (PARSING_CRASH);
	}
	ft_memcpy(node, champ, sizeof(t_champ));
	ft_add_champ(env, node);
	return (PARSING_RUNNING);
}

int			ft_parse_file(t_env *env, char *filename, int hasnumber, int number)
{
	t_champ	champ;
	t_champ	*ptr;

	ft_bzero(&champ, sizeof(t_champ));
	champ.filename = filename;
	champ.fd = open(filename, O_RDONLY);
	if (hasnumber)
	{
		ptr = env->champs;
		while (ptr)
		{
			if (ptr->number == -number)
			{
				ft_same_number_error(env, number);
				return (PARSING_ERROR);
			}
			ptr = ptr->next;
		}
		champ.number = -number;
		champ.hasnumber = 1;
	}
	return (ft_parse_file1(env, &champ));
}

int			ft_parsing_error(t_env *env, int error, char *s, char *s2)
{
	if (error == UNKNOWN_FLAG)
		ft_dprintf(2, "%s: Illegal option -- %s\n", env->prog_name, s);
	else if (error == FLAG_WITH_NC_ERROR)
		ft_dprintf(2, "%s: can't have flag : %s with flag : nc\n",
				env->prog_name, s);
	else if (error == NC_WITH_FLAGS_ERROR)
		ft_dprintf(2, "%s: can't have flag : %s with other flags than -a\n",
				env->prog_name, s);
	else if (error == PARAM_MISSING)
		ft_dprintf(2, "%s: missing argument after flag : %s\n", env->prog_name,
				s);
	else if (error == PARAM_FLAG_WRONG)
		ft_dprintf(2,
				"%s: wrong parameter after the value needing flag : %s (%s)\n",
				env->prog_name, s, s2);
	else if (error == CHAMP_MISSING)
		ft_dprintf(2,
			"%s: missing champ after flag : %s %s\n", env->prog_name, s, s2);
	else if (error == PARSING_OVERFLOW)
		ft_dprintf(2, "%s: Value : %s is too big ! (or too small)\n",
				env->prog_name, s);
	else if (error == PARAM_NEGATIVE)
		ft_dprintf(2, "%s: Illegal negative argument with flag : %s (%s)\n",
				env->prog_name, s, s2);
	return (PARSING_ERROR);
}
