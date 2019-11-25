/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 21:14:07 by toliver           #+#    #+#             */
/*   Updated: 2019/11/25 21:14:55 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_usage(void)
{
	ft_dprintf(2, "usage: ./asm [-%s] file ...\n", FLAGS);
	exit(0);
}

void		ft_wrong_flag(t_env *env, char c)
{
	ft_dprintf(2, "%s: illegal option -- %c\n", env->prog_name, c);
	ft_usage();
}

void		ft_crash(int error)
{
	t_env	*env;

	env = ft_get_env();
	ft_dprintf(2, "%s: ", env->prog_name);
	if (error == MALLOC_FAIL)
		ft_dprintf(2, "malloc failed: %s\n", strerror(errno));
	ft_free_env(env);
	exit(0);
}
