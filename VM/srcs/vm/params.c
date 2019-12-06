/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 06:20:18 by toliver           #+#    #+#             */
/*   Updated: 2019/12/06 07:26:06 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		ft_usage(t_env *env)
{
	ft_dprintf(2, "usage: %s [-a] [[-d N] [-s N] [-v N]] champion.cor ...\n", env->prog_name);
	exit(-1);
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

static int			ft_is_end_flag(char *flag)
{
	if (flag[0] == '-' && flag[1] == '-' && flag[2] == '\0')
		return (1);
	return (0);
}

static int			ft_is_flag(char *flag)
{
	if (flag[0] != '-')
		return (0);
	return (1);
}

static void		ft_parsing_error(t_env *env, int error, char c)
{
	if (error == PARAM_FLAG_WRONG)	
		ft_dprintf(2, "%s: Can't have a flag after the parameter needing flag : %c\n", env->prog_name, c);
	else if (error == UNKNOWN_FLAG)
		ft_dprintf(2, "%s: Illegal option -- %c\n", env->prog_name, c);
	else if (error == PARAM_MISSING) 
		ft_dprintf(2, "%s: missing argument after flag : %c\n", env->prog_name, c);
	else if (error == PARAM_NEGATIVE)
		ft_dprintf(2, "%s: Illegal negative argument with flag : %c\n", env->prog_name, c);

	exit(-1);
}

static void		ft_parse_param_flag_parameter(t_env *env, char **av, int *i, char flag)
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
	else if (flag== 'v')
		env->verbose_level |= number;
}


static int			ft_parse_flag(t_env *env, char **av, int *i)
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

int			ft_parse_params(t_env *env, char **av)
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
