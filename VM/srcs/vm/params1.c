/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 04:13:13 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 04:15:35 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			ft_usage(t_env *env)
{
	ft_dprintf(2, USAGE, env->prog_name);
	ft_dprintf(2, USAGE1_0, env->prog_name, USAGE1_1);
	ft_dprintf(2, USAGE2);
	ft_dprintf(2, USAGE3_0, USAGE3_1);
	ft_dprintf(2, USAGE4);
	ft_dprintf(2, USAGE5);
	ft_dprintf(2, USAGE6_0, USAGE6_1);
	ft_dprintf(2, "\t\t- 0 : Show only essentials\n");
	ft_dprintf(2, "\t\t- 1 : Show lives\n");
	ft_dprintf(2, "\t\t- 2 : Show cycles\n");
	ft_dprintf(2, "\t\t- 4 : Show operations (Params are NOT litteral ...\n");
	ft_dprintf(2, "\t\t- 8 : Show deaths\n");
	ft_dprintf(2, "\t\t- 16 : Show PC movements (Except for jump)\n");
	ft_dprintf(2, USAGE7_0, USAGE7_1);
	ft_dprintf(2, "\t-g\t: graphical (SDL) output mode\n");
	ft_dprintf(2, USAGE8_0, USAGE8_1);
	ft_dprintf(2, USAGE9_0, USAGE9_1);
}

int				ft_is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f'
			|| c == ' ')
		return (1);
	return (0);
}

int				ft_add_to_lst(t_params_list **lst, char *param)
{
	t_params_list	*node;
	t_params_list	*ptr;

	if (!(node = (t_params_list*)malloc(sizeof(t_params_list))))
	{
		ft_dprintf(2, "%s: Malloc failed: %s\n",
				ft_get_env()->prog_name, strerror(errno));
		return (0);
	}
	node->param = param;
	node->next = NULL;
	if (!(*lst))
		*lst = node;
	else
	{
		ptr = *lst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = node;
	}
	return (1);
}

int				ft_add_param(t_params_list **lst, char *param)
{
	int			i;

	i = 0;
	while (param[i])
	{
		while (ft_is_whitespace(param[i]))
		{
			param[i] = '\0';
			i++;
		}
		if (!param[i])
			break ;
		if (!ft_add_to_lst(lst, param + i))
			return (PARSING_CRASH);
		while (param[i] && !ft_is_whitespace(param[i]))
			i++;
	}
	return (PARSING_RUNNING);
}

void			ft_free_params_list(t_params_list *lst)
{
	t_params_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}
