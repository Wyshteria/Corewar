/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:34:54 by toliver           #+#    #+#             */
/*   Updated: 2020/01/03 22:41:05 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_verbose_flag(int flag)
{
	t_env	*env;

	env = ft_get_env();
	if ((env->flags & VERBOSE_FLAG) && (env->verbose_level & flag))
		return (1);
	return (0);
}
