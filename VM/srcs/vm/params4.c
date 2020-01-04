/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 04:19:36 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 04:22:00 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				ft_parse_param_size_t(t_env *env, t_params_list **lst,
		size_t *var)
{
	char		*prevflag;

	prevflag = (*lst)->param;
	*lst = (*lst)->next;
	if (*lst == NULL)
	{
		ft_parsing_error(env, PARAM_MISSING, prevflag + 1, (*lst)->param);
		return (PARSING_ERROR);
	}
	if (ft_is_containing_other_than((*lst)->param, "-+0123456789"))
	{
		ft_parsing_error(env, PARAM_FLAG_WRONG, prevflag + 1, (*lst)->param);
		return (PARSING_ERROR);
	}
	return (ft_parse_size_t(env, (*lst)->param, var, prevflag + 1));
}

int				ft_parse_param_int(t_env *env, t_params_list **lst, int *var)
{
	char		*prevflag;

	prevflag = (*lst)->param;
	*lst = (*lst)->next;
	if (*lst == NULL)
	{
		ft_parsing_error(env, PARAM_MISSING, prevflag + 1, NULL);
		return (PARSING_ERROR);
	}
	if (ft_is_containing_other_than((*lst)->param, "-+0123456789"))
	{
		ft_parsing_error(env, PARAM_FLAG_WRONG, prevflag + 1, (*lst)->param);
		return (PARSING_ERROR);
	}
	return (ft_parse_int(env, (*lst)->param, var));
}

int				ft_parse_param(t_env *env, t_params_list **lst, void *var,
		int is_size_t)
{
	if (is_size_t)
		return (ft_parse_param_size_t(env, lst, var));
	return (ft_parse_param_int(env, lst, var));
}

int				ft_parse_dump(t_env *env, t_params_list **lst)
{
	int			mode;

	if (env->flags & NCURSES_FLAG)
	{
		ft_parsing_error(env, FLAG_WITH_NC_ERROR, (*lst)->param + 1, NULL);
		return (PARSING_ERROR);
	}
	env->flags |= DUMP_FLAG;
	mode = ft_parse_param(env, lst, &(env->dump_cycles), 1);
	*lst = (*lst)->next;
	return (mode);
}

int				ft_parse_cycle_dump(t_env *env, t_params_list **lst)
{
	int			mode;

	if (env->flags & NCURSES_FLAG)
	{
		ft_parsing_error(env, FLAG_WITH_NC_ERROR, (*lst)->param + 1, NULL);
		return (PARSING_ERROR);
	}
	env->flags |= CYCLE_DUMP_FLAG;
	mode = ft_parse_param(env, lst, &(env->cycle_dump_cycles), 1);
	*lst = (*lst)->next;
	return (mode);
}
