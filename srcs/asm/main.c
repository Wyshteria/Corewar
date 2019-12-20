/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:18 by toliver           #+#    #+#             */
/*   Updated: 2019/11/29 17:46:06 by toliver          ###   ########.fr       */
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

// int			ft_parse_operations(t_env *env, t_file *file)
// {
// 	file->mode = PARSING;
// 	while (file->mode != DONE && file->mode != CRASH && file->mode != CONTAIN_ERRORS)
// 	{
// 		ft_skip_spaces(env, file);
// 		ft_parse_token(env, file);
// 	}
// 	if (file->mode == CRASH)
// 		ft_crash(MALLOC_FAIL);
// 	else if (file->mode == CONTAIN_ERRORS)
// 		return (0);
// 	return (1);

// }

int			ft_parse_file(t_env *env, t_file *file)
{
	while (file->mode != DONE && file->mode != CRASH && file->mode != CONTAIN_ERRORS)
	{
		ft_skip_spaces(env, file);
		ft_parse_token(env, file);
	}
	if (file->mode == CRASH)
		ft_crash(MALLOC_FAIL);
	else if (file->mode == DONE && (!file->header.prog_name[0]
	|| !file->header.comment[0]))
		return (ft_syntax_error(file, ft_last_token(file)));
	// else if (file->mode == DONE)
	// 	return (ft_parse_operations(env, file));
	else if (file->mode == CONTAIN_ERRORS)
		return (0);
	return (1);
}

int			ft_write_file(t_env *env, t_file *file)
{
	ft_printf("writing file !\n");
	ft_dump_tokens(file);
	ft_dump_env(env);
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
	// ft_dump_env(&env);
	ft_free_env(&env);
	return (0);
}
