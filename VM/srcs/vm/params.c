/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 06:20:18 by toliver           #+#    #+#             */
/*   Updated: 2019/12/30 07:12:15 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		ft_usage(t_env *env)
{
	ft_dprintf(2, "usage: %s [-a] [[-d[ump] N] [-s N] [-v N]] champion.cor ...\n",
			env->prog_name);
	ft_dprintf(2, "Usage: %s  [-d N -s N -v N | -nc] [-a] [-n N]<champion1.cor>\
		   	<...>\n", env->prog_name);
	ft_dprintf(2,"\t-a \t:Prints output from \"aff\" (Default is to hide it)\n");
	ft_dprintf(2,"####TEXT OUTPUT MODE #############################################\n");
	ft_dprintf(2,"\t-d[ump] N\t: Dumps memory after N cycles then exit\n");
	ft_dprintf(2,"\t-s N\t: Runs N cycles, dumps memory, pauses, then repeats\n");
	ft_dprintf(2,"\t-v N\t: Verbosity levels, can be added together to enable several\n");
	ft_dprintf(2,"\t\t- 0 : Show only essentials\n");
	ft_dprintf(2,"\t\t- 1 : Show lives\n");
	ft_dprintf(2,"\t\t- 2 : Show cycles\n");
	ft_dprintf(2,"\t\t- 4 : Show operations (Params are NOT litteral ...\n");
	ft_dprintf(2,"\t\t- 8 : Show deaths\n");
	ft_dprintf(2,"\t\t- 16 : Show PC movements (Except for jump)\n");
	ft_dprintf(2,"####NCURSES OUTPUT MODE ##########################################\n");
	ft_dprintf(2,"\t-nc\t: Ncurses output mode\n");
	ft_dprintf(2,"####CHAMPS PARAMS ################################################\n");
	ft_dprintf(2,"\t-n N\t: Set following champ number (is negated in process register)\n");
	exit(-1);
}

/*
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

static void		ft_parse_files(t_env *env, char *filename)
{
	t_champ	champ;
	t_champ	*node;

	ft_bzero(&champ, sizeof(t_champ));
	champ.filename = filename;
	champ.fd = open(filename, O_RDONLY);
	node = (t_champ*)ft_malloc(sizeof(t_champ));
	ft_memcpy(node, &champ, sizeof(t_champ));
	ft_add_champ(env, node);
}

static int		ft_is_end_flag(char *flag)
{
	if (flag[0] == '-' && flag[1] == '-' && flag[2] == '\0')
		return (1);
	return (0);
}

static int		ft_is_flag(char *flag)
{
	if (flag[0] != '-')
		return (0);
	return (1);
}

static void		ft_parsing_error(t_env *env, int error, char c)
{
	if (error == PARAM_FLAG_WRONG)
		ft_dprintf(2,
				"%s: Can't have a flag after the parameter needing flag : %c\n",
				env->prog_name, c);
	else if (error == UNKNOWN_FLAG)
		ft_dprintf(2, "%s: Illegal option -- %c\n", env->prog_name, c);
	else if (error == PARAM_MISSING)
		ft_dprintf(2, "%s: missing argument after flag : %c\n", env->prog_name,
				c);
	else if (error == PARAM_NEGATIVE)
		ft_dprintf(2, "%s: Illegal negative argument with flag : %c\n",
				env->prog_name, c);
	exit(-1);
}

static void		ft_parse_param_flag_parameter(t_env *env, char **av, int *i,
		char flag)
{
	int		number;

	if (*i >= env->ac)
		ft_parsing_error(env, PARAM_MISSING, flag);
	if (ft_is_containing_other_than(av[*i], "+-0123456789"))
		ft_parsing_error(env, PARAM_MISSING, flag); // PENSER SI ON GERE LE NUMERO DU CHAMPION A LE PARSER ICI
	number = ft_atoi(av[*i]);
	if (number < 0)
		ft_parsing_error(env, PARAM_NEGATIVE, flag);
	if (flag == 'd')
		env->dump_cycles = number;
	else if (flag == 's')
		env->cycle_dump_cycles = number;
	else if (flag == 'v')
		env->verbose_level |= number;
}

*/

/*
static int		ft_parse_flag(t_env *env, char **av, int *i)
{
	int		j;

	j = 1;
	if (ft_is_end_flag(av[*i]) || !ft_is_flag(av[*i]))
	{
		*i += ft_is_end_flag(av[*i]) ? 1 : 0;
		return (PARSE_FILES);
	}
	while (ft_is_one_of(av[*i][j], CONCATABLE_FLAGS))
	{
		env->flags |= ft_pow2(ft_strchr_pos(CONCATABLE_FLAGS, av[*i][j]));
		j++;
	}
	if (ft_is_one_of(av[*i][j], PARAMS_FLAGS))
	{
		env->flags |= ft_pow2(ft_strchr_pos(PARAMS_FLAGS, av[*i][j])
				+ ft_strlen(CONCATABLE_FLAGS));
		if (av[*i][j + 1] != '\0')
			ft_parsing_error(env, PARAM_FLAG_WRONG, av[*i][j]);
		*i += 1;
		ft_parse_param_flag_parameter(env, av, i, av[*i - 1][j]);
	}
	else if (av[*i][j] != '\0')
		ft_parsing_error(env, UNKNOWN_FLAG, av[*i][j]);
	*i += 1;
	return (PARSE_FLAGS);
}
*/

// compter -d et -dump comme les memes, compter le -n pour assigner un numero a un champ

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
			break;
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

int			ft_parse_file(t_env *env, char *filename, int hasnumber, int number)
{
	t_champ	champ;
	t_champ	*node;

	ft_bzero(&champ, sizeof(t_champ));
	champ.filename = filename;
	champ.fd = open(filename, O_RDONLY);
	if (hasnumber)
		champ.number = number;
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

static void		ft_parsing_error(t_env *env, int error, char* s)
{
	if (error == UNKNOWN_FLAG)
		ft_dprintf(2, "%s: Illegal option -- %s\n", env->prog_name, s);
	else if (error == FLAG_WITH_NC_ERROR)
		ft_dprintf(2, "%s: can't have flag : %s with flag : nc\n",
				env->prog_name, s);
	else if (error == NC_WITH_FLAGS_ERROR)
		ft_dprintf(2, "%s: can't have flag : %s with other flags than -a\n",
				env->prog_name, s);

	else if (error == PARAM_FLAG_WRONG)
		ft_dprintf(2,
				"%s: Can't have a flag after the parameter needing flag : %s\n",
				env->prog_name, s);
	else if (error == PARAM_MISSING)
		ft_dprintf(2, "%s: missing argument after flag : %s\n", env->prog_name,
				s);
	else if (error == PARAM_NEGATIVE)
		ft_dprintf(2, "%s: Illegal negative argument with flag : %s\n",
				env->prog_name, s);
//	exit(-1);
}
int				ft_parse_param(t_env *env, t_params_list **lst, void *var,
		int is_size_t)
{
	(void)env;
	(void)lst;
	(void)var;
	(void)is_size_t;
	ft_printf("parse param !\n"); // penser a parser le parametre
	*lst = (*lst)->next;
	return (PARSING_RUNNING);
}


int				ft_parse_dump(t_env *env, t_params_list **lst)
{
	if (env->flags & NCURSES_FLAG)
	{
		ft_parsing_error(env, FLAG_WITH_NC_ERROR, (*lst)->param + 1);
		return (PARSING_ERROR);
	}
	ft_printf("dump flag !\n"); // penser a parser le parametre
	env->flags |= DUMP_FLAG;
	*lst = (*lst)->next;
	return (ft_parse_param(env, lst, &(env->dump_cycles), 1));
}

int				ft_parse_cycle_dump(t_env *env, t_params_list **lst)
{
	if (env->flags & NCURSES_FLAG)
	{
		ft_parsing_error(env, FLAG_WITH_NC_ERROR, (*lst)->param + 1);
		return (PARSING_ERROR);
	}
	ft_printf("cycle dump flag !\n"); // penser a parser le parametre
	env->flags |= CYCLE_DUMP_FLAG;
	*lst = (*lst)->next;
	return (ft_parse_param(env, lst, &(env->cycle_dump_cycles), 1));
}

int				ft_parse_nc(t_env *env, t_params_list **lst)
{
	if (env->flags & FORBIDDEN_NC_FLAGS)
	{
		ft_parsing_error(env, NC_WITH_FLAGS_ERROR, (*lst)->param + 1);
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

	number = 0;
	*lst = (*lst)->next;
	ft_printf("champ_number flag !\n"); // penser a parser le parametre
	mode = ft_parse_param(env, lst, &number, 0);
	if (mode == PARSING_RUNNING)
	{
		ft_printf("parsing champ : %s\n", (*lst)->param);
		mode = ft_parse_file(env, (*lst)->param, 1, number);
		*lst = (*lst)->next;
	}
	return (mode);
}

int				ft_parse_verbose(t_env *env, t_params_list **lst)
{
	if (env->flags & NCURSES_FLAG)
	{
		ft_parsing_error(env, FLAG_WITH_NC_ERROR, (*lst)->param + 1);
		return (PARSING_ERROR);
	}
	*lst = (*lst)->next;
	env->flags |= VERBOSE_FLAG;
	ft_printf("verbose flag !\n"); // penser a parser le parametre
	return (PARSING_RUNNING);
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
		ft_parsing_error(env, UNKNOWN_FLAG, (*lst)->param + i);
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
			ft_printf("parsing champ : %s\n", lst->param);
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
		ft_usage(env);
	mode = ft_parse_all_params(env, av);
	if (mode == PARSING_ERROR || mode == PARSING_CRASH)
		return (0);
	return (1);
}

/*
int				ft_parse_params(t_env *env, char **av)
{
	int		i;
	int		mode;

	i = 0;
	mode = PARSE_FLAGS;
	if (env->ac == 0)
		ft_usage(env);
	while (mode == PARSE_FLAGS && i < env->ac)
		mode = ft_parse_flag(env, av, &i);
	while (mode == PARSE_FILES && i < env->ac)
	{
		ft_parse_files(env, av[i]);
		i++;
	}
	return (1);
}
 */
