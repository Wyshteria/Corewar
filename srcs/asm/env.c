/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 21:15:07 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 09:29:20 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_env		**ft_get_envptr(void)
{
	static t_env	*env = NULL;

	return (&env);
}

t_env				*ft_get_env(void)
{
	return (*(ft_get_envptr()));
}

void				ft_set_env(t_env *env)
{
	*(ft_get_envptr()) = env;
}

void				ft_init_env(t_env *env, char *prog_name)
{
	ft_bzero(env, sizeof(t_env));
	env->prog_name = prog_name;
}

void				ft_free_env(t_env *env)
{
	ft_free_files(env);
	ft_free_op(&env->prog);
	ft_free_label(&env->prog);
	free(env->prog.filename);
}
