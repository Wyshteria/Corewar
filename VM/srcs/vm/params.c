/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 06:20:18 by toliver           #+#    #+#             */
/*   Updated: 2019/12/30 09:42:00 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		ft_usage(t_env *env)
{
	ft_dprintf(2, "usage: %s [-a] [[-d[ump] N] [-s N] [-v N]] champion.cor ...\n",
			env->prog_name);
	ft_dprintf(2, "Usage: %s  [-d N -s N -v N | -nc] [-a] [-n N]<champion1.cor> <...>\n", env->prog_name);
	ft_dprintf(2, "\t-a \t:Prints output from \"aff\" (Default is to hide it)\n");
	ft_dprintf(2, "####TEXT OUTPUT MODE #############################################\n");
	ft_dprintf(2, "\t-d[ump] N\t: Dumps memory after N cycles then exit\n");
	ft_dprintf(2, "\t-s N\t: Runs N cycles, dumps memory, pauses, then repeats\n");
	ft_dprintf(2, "\t-v N\t: Verbosity levels, can be added together to enable several\n");
	ft_dprintf(2, "\t\t- 0 : Show only essentials\n");
	ft_dprintf(2, "\t\t- 1 : Show lives\n");
	ft_dprintf(2, "\t\t- 2 : Show cycles\n");
	ft_dprintf(2, "\t\t- 4 : Show operations (Params are NOT litteral ...\n");
	ft_dprintf(2, "\t\t- 8 : Show deaths\n");
	ft_dprintf(2, "\t\t- 16 : Show PC movements (Except for jump)\n");
	ft_dprintf(2, "####NCURSES OUTPUT MODE ##########################################\n");
	ft_dprintf(2, "\t-nc\t: Ncurses output mode\n");
	ft_dprintf(2, "####CHAMPS PARAMS ################################################\n");
	ft_dprintf(2, "\t-n N\t: Set following champ number (is negated in process register)\n");
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

static void		ft_add_champ(t_env *env, t_champ *champ)
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

int			ft_parse_file(t_env *env, char *filename, int hasnumber, int number)
{
	t_champ	champ;
	t_champ	*node;
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
	if (!(node = (t_champ*)ft_malloc(sizeof(t_champ))))
	{
		ft_dprintf(2, "%s: Malloc failed: %s\n",
				ft_get_env()->prog_name, strerror(errno));
		return (PARSING_CRASH);
	}
	ft_memcpy(node, &champ, sizeof(t_champ));
	ft_add_champ(env, node);
	return (PARSING_RUNNING);
}

static void		ft_parsing_error(t_env *env, int error, char *s, char *s2)
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
}

int				ft_parse_int(t_env *env, char *s, int *ptr)
{
	int			i;
	int			value;
	char		*check;

	value = ft_atoi(s);
	check = ft_itoa(value);
	if (!check)
	{
		ft_dprintf(2, "%s: Malloc failed: %s\n",
				ft_get_env()->prog_name, strerror(errno));
		return (PARSING_CRASH);
	}
	i = 0;
	if (s[0] == '+')
		s++;// si onmet +- ca met too big mais osef
	while (check[i] && s[i] && check[i] == s[i])
		i++;
	if (check[i])
	{
		free(check);
		ft_parsing_error(env, PARSING_OVERFLOW, s, NULL);
		return (PARSING_ERROR);
	}
	free(check);
	*ptr = value;
	return (PARSING_RUNNING);
}

static int			nbr_sizet(size_t nb)
{
	int				nbrsize;

	nbrsize = 1;
	while (nb > 9)
	{
		nb /= 10;
		nbrsize++;
	}
	return (nbrsize);
}

char				*ft_sizettoa(size_t nbr)
{
	char			*str;
	int				nbrsize;

	nbrsize = nbr_sizet(nbr);
	if (!(str = (char*)malloc(sizeof(char) * (nbrsize + 1))))
		return (NULL);
	str[nbrsize] = '\0';
	if (nbr == 0)
		str[0] = '0';
	while (nbr != 0)
	{
		str[nbrsize - 1] = nbr % 10 + '0';
		nbr /= 10;
		nbrsize--;
	}
	return (str);
}

size_t			ft_atosize_t(char *str)
{
	size_t		result;

	result = 0;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

int				ft_parse_size_t(t_env *env, char *s, size_t *ptr, char *flag)
{
	int			i;
	size_t		value;
	char		*check;

	if (s[0] == '-' || (s[0] == '+' && s[1] == '-'))
	{
		ft_parsing_error(env, PARAM_NEGATIVE, flag, s);
		return (PARSING_ERROR);
	}
	value = ft_atosize_t(s);
	check = ft_sizettoa(value);
	if (!check)
	{
		ft_dprintf(2, "%s: Malloc failed: %s\n",
			ft_get_env()->prog_name, strerror(errno));
		return (PARSING_CRASH);
	}
	i = 0;
	if (s[0] == '+')
		s++;
	while (check[i] && s[i] && check[i] == s[i])
		i++;
	if (s[i])
	{
		free(check);
		ft_parsing_error(env, PARSING_OVERFLOW, s, NULL);
		return (PARSING_ERROR);
	}
	free(check);
	*ptr = value;
	return (PARSING_RUNNING);
}

int				ft_parse_param_size_t(t_env *env, t_params_list **lst, size_t *var)
{
	char		*prevflag;

	(void)var;
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
	else if (!ft_strcmp((*lst)->param + i, "nc"))
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
