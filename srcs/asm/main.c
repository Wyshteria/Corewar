/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboukrou <lboukrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:18 by toliver           #+#    #+#             */
/*   Updated: 2020/01/05 03:13:04 by lboukrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_open_file(t_env *env, t_file *file)
{
	int		fd;

	fd = open(file->filename, O_RDONLY);
	file->fd = fd;
	if (fd == -1)
	{
		ft_error(env, file, OPEN_ERROR);
		return (0);
	}
	return (1);
}

void		ft_delete_file(t_env *env, t_file *file)
{
	t_file	*ptr;

	if (env->files == file)
		env->files = file->next;
	else
	{
		ptr = env->files;
		while (ptr->next != file)
			ptr = ptr->next;
		ptr->next = file->next;
	}
	ft_free_file(file);
}

int			ft_parse_operations(t_env *env, t_file *file)
{
	if (!ft_init_prog(env, file))
	{
		ft_clear_prog(&env->prog);
		if (file->mode != CRASH)
			file->mode = CONTAIN_ERRORS;
		return (0);
	}
	return (1);
}

int			ft_write_file(t_env *env, t_file *file)
{
	int		ret;

	ft_clear_prog(&env->prog);
	if (!ft_parse_operations(env, file))
		return (0);
	if (!(ret = ft_open_cor_file(&(env->prog), env, file)))
		return (0);
	if (ret == -1)
		ft_printf("Cor file %s generated but corrupted\n", env->prog.filename);
	else
		ft_printf("Cor file %s generated\n", env->prog.filename);
	return (1);
}

int			main(int ac, char **av)
{
	t_env	env;

	ft_init_env(&env, av[0]);
	ft_set_env(&env);
	ft_parse_args(ac, av, &env);
	ft_parse_files(&env);
	ft_free_env(&env);
	return (0);
}
