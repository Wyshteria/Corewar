/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:18 by toliver           #+#    #+#             */
/*   Updated: 2019/11/25 22:43:58 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_dump_file(t_file *file)
{
	ft_printf("\tfile name = %s\n", file->filename);
	ft_printf("\tfile fd = %d\n", file->fd);
}

void		ft_dump_files(t_file *files)
{
	t_file	*ptr;

	ptr = files;
	while (ptr)
	{
		ft_dump_file(ptr);
		ptr = ptr->next;
	}
}

void		ft_dump_env(t_env *env)
{
	ft_printf("prog name : %s\n", env->prog_name);
	ft_printf("prog flags = %b\n", env->flags);
	ft_dump_files(env->files);
}

int			ft_error(t_env *env, t_file *file, int error)
{
	(void)error;
	ft_dprintf(2, "%s: %s: %s\n", env->prog_name, file->filename, strerror(errno));
	return (0);
}

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

int			ft_parse_file(t_env *env, t_file *file)
{
	(void)env;
	(void)file;
	ft_printf("parsing file !\n");
	return (1);
}

int			ft_write_file(t_env *env, t_file *file)
{
	(void)env;
	(void)file;
	ft_printf("writing file !\n");
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
//			ft_delete_file(env, tmp); pareil que dessous
			continue;
		}
		else if (!(ft_parse_file(env, ptr)))
		{
			close(ptr->fd);
			tmp = ptr;
			ptr = ptr->next;
//			ft_delete_file(env, tmp); pareil que dessous
			continue;
		}
		else if (!(ft_write_file(env, ptr)))
		{
			close(ptr->fd);
			tmp = ptr;
			ptr = ptr->next;
//			ft_delete_file(env, tmp); pareil que dessous
			continue;
		}
		close(ptr->fd);
		tmp = ptr;
//		ft_delete_file(env, tmp); penser a decomenter pour retrouver les files dans le dump
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
	ft_dump_env(&env);
	ft_free_env(&env);
	return (0);
}
