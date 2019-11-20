/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:18 by toliver           #+#    #+#             */
/*   Updated: 2019/11/20 23:09:04 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

int			ft_error(t_env *env, int error)
{
	env->mode = CRASH;
	env->error.value = error;
	return (0);
}

int			ft_parse_flags(t_env *env, char *flag)
{
	int		i;
	int		pos;
	int		flags;

	i = 0;
	flags = 0;
	if (flag[0] != '-' || (flag[0] == '-' && flag[1] == '-'))
	{
		env->mode = PARSING_FILES;
		return (0);
	}
	flag++;
	while (flag[i])
	{
		if ((pos = ft_strchr_pos(FLAGS, flag[i])) == -1)
		{
			env->error.flag_error = flag[i];
			return (ft_error(env, WRONG_FLAGS));
		}
		flags = flags | ft_pow2(pos);
		i++;
	}
	env->flags |= flags;
	return (1);
}

void		ft_open_error(char *name, char *file)
{
	ft_dprintf(2, "%s: %s: %s\n", name, file, strerror(errno));
}

void		ft_parse_files(t_env *env, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_open_error(env->prog_name, file);
		return;
	}
	if (env->mode != CRASH)
		env->mode = PARSING_FILES;
}

void		ft_parse_args(int ac, char **av, t_env *env)
{
	int		i;

	i = 0;
	env->mode = PARSING_FLAGS;
	if (ac == 0)
		ft_error(env, NO_PARAMS);
	while (i < ac && env->mode != CRASH)
	{
		if (env->mode == PARSING_FLAGS)
		{
			if (ft_parse_flags(env, av[i]))
				i++;
		}
		if (env->mode == PARSING_FILES)
		{
			ft_parse_files(env, av[i]);
			i++;
		}
	}
	if (env->mode != CRASH)
		env->mode = PARSING_FILES;
}

void		ft_dump_env(t_env *env)
{
	ft_printf("env mode = %d\n", env->mode);
	ft_printf("env error = %d\n", env->error.value);
	ft_printf("flags = %d, en binaire : %b\n", env->flags, env->flags);
}

void		ft_usage(t_error *error)
{
	if (error->value == WRONG_FLAGS)
		ft_dprintf(2, "illegal option -- %c\n", error->flag_error);
	ft_dprintf(2, "usage: ./asm [-%s] file ...\n", FLAGS);	
}

void		ft_print_error(char *program, t_error *error)
{
	ft_dprintf(2, "%s: ", program);
	if (error->value == NO_PARAMS || error->value == WRONG_FLAGS)
		ft_usage(error);
	else
		ft_putstr_fd("unknown error\n", 2);
}

int			main(int ac, char **av)
{
	t_env	env;

	env.prog_name = av[0];
	env.mode = PARSING_ARGS;
	ft_parse_args(ac - 1, av + 1, &env);
	if (env.mode != CRASH)
		ft_putstr("ca crash pas !\n");
	if (env.mode == CRASH)
		ft_print_error(env.prog_name, &env.error);
//	ft_dump_env(&env);
	return (0);
}
