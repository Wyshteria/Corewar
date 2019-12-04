/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:18 by toliver           #+#    #+#             */
/*   Updated: 2019/12/04 04:20:59 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_pow2(int pow)
{
	int		i;
	int		value;

	if (pow < 0)
		return (0);
	value = 1;
	i = 0;
	while (i < pow)
	{
		value *= 2;
		i++;
	}
	return (value);
}

int			ft_strchr_pos(char *str, int c)
{
	char	*val;

	val = ft_strchr(str, c);
	if (val == NULL)
		return (-1);
	return ((int)(val - str));
}

int			ft_is_one_of(char c, char *lookfor)
{
	int		i;
	
	i = 0;
	while (lookfor && lookfor[i])
	{
		if (lookfor[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void			ft_usage(t_env *env)
{
	ft_dprintf(2, "usage: %s [-a] [[-d N] [-s N] [-v N]] champion.cor ...\n", env->prog_name);
	exit(-1);
}

void		ft_param_flags_wrong(t_env *env, char c)
{
	ft_dprintf(2, "%s: Can't have a flag after the parameter needing flag : %c\n", env->prog_name, c);
	exit(-1);
}

void		ft_unknown_flag(t_env *env, char c)
{
	ft_dprintf(2, "%s: Illegal option -- %c\n", env->prog_name, c);
	ft_usage(env);
}

void		ft_negative_param(int number, t_env *env)
{
	ft_dprintf(2, "%s: Illegal negative argument : %d\n", env->prog_name, number);
	exit(-1);
}

void		ft_missing_param(t_env *env, char flag)
{
	ft_dprintf(2, "%s: missing argument after flag : %c\n", env->prog_name, flag);
	exit(-1);
}

int			ft_is_containing_other_than(char *str, char *containing)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_one_of(str[i], containing))
			return (1);
		i++;
	}
	return (0);
}

void		ft_parse_param_flag_parameter(t_env *env, char **av, int *i, char flag)
{
	int		number;

	if (*i >= env->ac)
		ft_missing_param(env, flag);
 	if (ft_is_containing_other_than(av[*i], "+-0123456789"))
		ft_missing_param(env, flag);
	number = ft_atoi(av[*i]);
	if (number < 0)
		ft_negative_param(number, env);
	if (flag == 'd')
		env->dump_cycles = number;
	else if (flag == 's')
		env->cycle_dump_cycles = number;
	else if (flag== 'v')
		env->verbose_level |= number;
}

void		ft_parse_flag(t_env *env, char **av, int *i, int *mode)
{
	int		j;

	if ((av[*i][0] == '-' && av[*i][1] == '-' && av[*i][2] == 0) || av[*i][0] != '-')
	{
		*mode = PARSE_FILES;
		if (av[*i][0] == '-')
			*i += 1;
	}
	else if (av[*i][0] == '-')
	{
		j = 1;
		while (ft_is_one_of(av[*i][j], CONCATABLE_FLAGS))
		{
			env->flags |= ft_pow2(ft_strchr_pos(CONCATABLE_FLAGS, av[*i][j]));
			j++;
		}
		if (ft_is_one_of(av[*i][j], PARAMS_FLAGS))
		{
			env->flags |= ft_pow2(ft_strchr_pos(PARAMS_FLAGS, av[*i][j]) + ft_strlen(CONCATABLE_FLAGS));
			if (av[*i][j + 1] != '\0')
				ft_param_flags_wrong(env, av[*i][j]);
			*i += 1;
			ft_parse_param_flag_parameter(env, av, i, av[*i - 1][j]);
		}
		else if (av[*i][j] != '\0')
			ft_unknown_flag(env, av[*i][j]);
		*i += 1;
	}
}

int			ft_parse_params(t_env *env, int ac, char **av)
{
	int		i;
	int		mode;


	i = 0;
	mode = PARSE_FLAGS;
	if (ac == 0)
		ft_usage(env);
	while (i < ac && mode != PARSE_ERROR && mode != PARSE_CRASH)
	{
		while (mode == PARSE_FLAGS && i < ac)
			ft_parse_flag(env, av, &i, &mode);
		if (mode == PARSE_FILES)
		{
			ft_printf("%s\n", av[i]);
			i++;
		}
	}
	return (1);
}

int			ft_env_init(t_env *env, char *progname, int ac)
{
	env->prog_name = progname;
	env->ac = ac;
	return (1);
}

void		ft_dump_verbose_flags(t_env *env)
{
	if (env->verbose_level == 0)
		ft_printf(" only essentials\n");
	else
	{
		ft_printf(":\n");
		if (env->verbose_level & VERBOSE_LIVES_FLAG)
			ft_printf("\t\t- show lives\n");
		if (env->verbose_level & VERBOSE_CYCLES_FLAG)
			ft_printf("\t\t- show cycles\n");
		if (env->verbose_level & VERBOSE_OPERATIONS_FLAG)
			ft_printf("\t\t- show operations (Params are NOT litteral ...)\n");
		if (env->verbose_level & VERBOSE_DEATH_FLAG)
			ft_printf("\t\t- show deaths\n");
		if (env->verbose_level & VERBOSE_PC_MOVEMENT_FLAG)
			ft_printf("\t\t- show PC movements (Except for jumps)\n");
	}
}

void		ft_dump_flags(t_env *env)
{
	if (env->flags & AFF_FLAG)
		ft_printf("\tPrint output from 'aff'\n");
	if (env->flags & DUMP_FLAG)
		ft_printf("\tDump memory after %zu cycles then exit\n", env->dump_cycles);
	if (env->flags & CYCLE_DUMP_FLAG)	
		ft_printf("\tDump memory every %zu cycles\n", env->cycle_dump_cycles);
	if (env->flags & VERBOSE_FLAG)
	{
		ft_printf("\tVerbose is activated with ");
		ft_dump_verbose_flags(env);
	}
}

void		ft_dump_env(t_env *env)
{
	ft_printf("prog_name = %s\n", env->prog_name);
	ft_printf("with flags :\n");
	ft_dump_flags(env);
}

int			main(int ac, char **av)
{
	t_env	env;

	ft_bzero(&env, sizeof(t_env));
	ft_env_init(&env, av[0], ac - 1);
	if (!ft_parse_params(&env, ac - 1, av + 1))
		return (-1);
	ft_dump_env(&env);

	return (0);
}
