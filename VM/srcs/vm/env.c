/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 00:04:12 by toliver           #+#    #+#             */
/*   Updated: 2019/12/27 21:57:20 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

int					ft_env_init(t_env *env, char *progname, int ac)
{
	ft_bzero(env, sizeof(t_env));
	env->prog_name = progname;
	env->ac = ac;
	ft_set_env(env);
	return (1);
}
