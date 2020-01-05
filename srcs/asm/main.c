/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboukrou <lboukrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:18 by toliver           #+#    #+#             */
/*   Updated: 2020/01/05 00:42:42 by lboukrou         ###   ########.fr       */
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
		if (file->mode != CRASH)
			file->mode = CONTAIN_ERRORS;
		return (0);
	}
	return (1);
}

int			ft_parse_file(t_env *env, t_file *file)
{
	while (file->mode != DONE && file->mode != CRASH
			&& file->mode != CONTAIN_ERRORS)
	{
		ft_skip_spaces(env, file);
		ft_parse_token(env, file);
	}
	return (file->mode != CRASH && file->mode != CONTAIN_ERRORS);
}

int			ft_write_file(t_env *env, t_file *file)
{

	ft_clear_prog(&env->prog);
	if (!ft_parse_operations(env, file))
		return(0);
	if (!ft_open_cor_file(&(env->prog), env, file))
		return (0);
	ft_printf("Cor file %s generated\n", env->prog.filename);
	return (1);
}

void		ft_parse_files(t_env *env)
{
	t_file	*ptr;
	t_file	*tmp;

	ptr = env->files;
	while (ptr)
	{
		if (!(ft_open_file(env, ptr)))
		{
			tmp = ptr;
			ptr = ptr->next;
			ft_delete_file(env, tmp);
			continue;
		}
		else if (!(ft_parse_file(env, ptr)))
		{
			close(ptr->fd);
			tmp = ptr;
			ptr = ptr->next;
			ft_delete_file(env, tmp);
			continue;
		}
		else if (!(ft_write_file(env, ptr)))
		{
			close(ptr->fd);
			tmp = ptr;
			ptr = ptr->next;
			ft_delete_file(env, tmp);
			continue;
		}
		close(ptr->fd);
		tmp = ptr;
		ft_delete_file(env, tmp);
		ptr = ptr->next;
	}
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
