/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 04:22:55 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 04:24:09 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				ft_parse_nc(t_env *env, t_params_list **lst)
{
	if (env->flags & FORBIDDEN_NC_FLAGS)
	{
		ft_parsing_error(env, NC_WITH_FLAGS_ERROR, (*lst)->param + 1, NULL);
		return (PARSING_ERROR);
	}
	*lst = (*lst)->next;
	env->flags |= NCURSES_FLAG;
	return (PARSING_RUNNING);
}

int				ft_parse_aff(t_env *env, t_params_list **lst)
{
	*lst = (*lst)->next;
	env->flags |= AFF_FLAG;
	return (PARSING_RUNNING);
}

int				ft_parse_champ_number(t_env *env, t_params_list **lst)
{
	int			mode;
	int			number;
	char		*value;

	number = 0;
	mode = ft_parse_param(env, lst, &number, 0);
	value = (*lst)->param;
	if (mode == PARSING_RUNNING)
	{
		*lst = (*lst)->next;
		if (*lst == NULL)
		{
			ft_parsing_error(env, CHAMP_MISSING, "-n", value);
			return (PARSING_ERROR);
		}
		mode = ft_parse_file(env, (*lst)->param, 1, number);
		*lst = (*lst)->next;
	}
	return (mode);
}
