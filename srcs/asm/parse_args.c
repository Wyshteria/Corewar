/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 21:12:20 by toliver           #+#    #+#             */
/*   Updated: 2019/12/04 04:09:22 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int			ft_parse_flags(t_env *env, char *flag)
{
	int		i;
	int		pos;
	int		flags;

	i = 0;
	flags = 0;
	if (flag[0] != '-' || (flag[0] == '-' && flag[1] == '-'))
		return (0);
	flag++;
	while (flag[i])
	{
		if ((pos = ft_strchr_pos(FLAGS, flag[i])) == -1)
			ft_wrong_flag(env, flag[i]);
		flags = flags | ft_pow2(pos);
		i++;
	}
	env->flags |= flags;
	return (1);
}

static void		ft_parse_files(t_env *env, char *file)
{
	t_file	*ptr;
	t_file	*tmp;

	ptr = (t_file*)ft_malloc(sizeof(t_file));
	ft_bzero(ptr, sizeof(t_file));
	ft_bzero(ptr->header.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(ptr->header.comment, COMMENT_LENGTH + 1);
	ptr->line++;
	ptr->col++;
	ptr->filename = file;
	if (env->files == NULL)
		env->files = ptr;
	else
	{
		tmp = env->files;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ptr;
	}
}

void		ft_parse_args(int ac, char **av, t_env *env)
{
	int		i;
	int		mode;

	i = 1;
	mode = PARSING_FLAGS;
	if (ac == 1)
		ft_usage();
	while (i < ac)
	{
		if (mode == PARSING_FLAGS)
		{
			if (ft_parse_flags(env, av[i]))
				i++;
			else
				mode = PARSING_FILES;
		}
		if (mode == PARSING_FILES)
		{
			ft_parse_files(env, av[i]);
			i++;
		}
	}
}


