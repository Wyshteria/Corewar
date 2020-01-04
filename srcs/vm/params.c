/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 06:20:18 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 04:24:07 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				ft_parse_verbose(t_env *env, t_params_list **lst)
{
	int			mode;

	if (env->flags & NCURSES_FLAG)
	{
		ft_parsing_error(env, FLAG_WITH_NC_ERROR, (*lst)->param + 1, NULL);
		return (PARSING_ERROR);
	}
	env->flags |= VERBOSE_FLAG;
	mode = ft_parse_param(env, lst, &(env->verbose_level), 0);
	*lst = (*lst)->next;
	return (mode);
}

int				ft_parse_flag(t_env *env, t_params_list **lst)
{
	int			i;

	i = 1;
	if (!ft_strcmp((*lst)->param + i, "dump") ||
			!ft_strcmp((*lst)->param + i, "d"))
		return (ft_parse_dump(env, lst));
	else if (!ft_strcmp((*lst)->param + i, "g"))
		return (ft_parse_nc(env, lst));
	else if (!ft_strcmp((*lst)->param + i, "v"))
		return (ft_parse_verbose(env, lst));
	else if (!ft_strcmp((*lst)->param + i, "s"))
		return (ft_parse_cycle_dump(env, lst));
	else if (!ft_strcmp((*lst)->param + i, "a"))
		return (ft_parse_aff(env, lst));
	else if (!ft_strcmp((*lst)->param + i, "n"))
		return (ft_parse_champ_number(env, lst));
	else
	{
		ft_parsing_error(env, UNKNOWN_FLAG, (*lst)->param + i, NULL);
		return (PARSING_ERROR);
	}
	*lst = (*lst)->next;
	return (PARSING_RUNNING);
}

int				ft_parse_params_list(t_env *env, t_params_list *lst)
{
	int			mode;

	mode = PARSING_RUNNING;
	while (lst && mode == PARSING_RUNNING)
	{
		if (lst->param[0] == '-')
			mode = ft_parse_flag(env, &lst);
		else
		{
			mode = ft_parse_file(env, lst->param, 0, 0);
			lst = lst->next;
		}
	}
	return (mode);
}

int				ft_parse_all_params(t_env *env, char **av)
{
	t_params_list	*list;
	int				i;
	int				mode;

	list = NULL;
	i = 0;
	mode = PARSING_RUNNING;
	while (i < env->ac && mode == PARSING_RUNNING)
	{
		mode = ft_add_param(&list, av[i]);
		i++;
	}
	if (mode == PARSING_CRASH)
	{
		ft_free_params_list(list);
		return (mode);
	}
	mode = ft_parse_params_list(env, list);
	ft_free_params_list(list);
	return (mode);
}

int				ft_parse_params(t_env *env, char **av)
{
	int		mode;

	if (env->ac == 0)
	{
		ft_usage(env);
		return (0);
	}
	mode = ft_parse_all_params(env, av);
	if (mode == PARSING_ERROR || mode == PARSING_CRASH)
		return (0);
	return (1);
}
