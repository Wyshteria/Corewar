/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 23:52:15 by toliver           #+#    #+#             */
/*   Updated: 2020/01/03 22:41:30 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_dump_flags(t_env *env)
{
	if (env->flags & AFF_FLAG)
		ft_printf("\tPrint output from 'aff'\n");
	if (env->flags & DUMP_FLAG)
		ft_printf("\tDump memory after %zu cycles then exit\n",
				env->dump_cycles);
	if (env->flags & CYCLE_DUMP_FLAG)
		ft_printf("\tDump memory every %zu cycles\n",
				env->cycle_dump_cycles);
	if (env->flags & VERBOSE_FLAG)
	{
		ft_printf("\tVerbose is activated with ");
		ft_dump_verbose_flags(env);
	}
}

void		ft_dump_header(t_header *header)
{
	ft_printf("\t\t\tmagic number : %#06x\n", header->magic);
	ft_printf("\t\t\tname : %s\n", header->prog_name);
	ft_printf("\t\t\tprog size = %u\n", header->prog_size);
	ft_printf("\t\t\tcomment = %s\n", header->comment);
}

void		ft_dump_content(t_champ *champ)
{
	uint32_t		i;

	i = 0;
	while (i < champ->header.prog_size)
	{
		ft_printf("0x%.2hhx ", champ->content[i]);
		i++;
	}
	ft_printf("\n");
}

void		ft_dump_champs(t_env *env)
{
	t_champ	*ptr;

	ptr = env->champs;
	ft_printf("Contains champs :\n");
	while (ptr)
	{
		ft_printf("\tChampion in file %s\n", ptr->filename);
		ft_printf("\t\tWith number %u\n", ptr->number);
		ft_printf("\t\tWith fd : %d\n", ptr->fd);
		ft_printf("\t\tWith header :\n");
		ft_dump_header(&(ptr->header));
		ft_printf("\t\twhich contains :\n");
		ft_dump_content(ptr);
		ptr = ptr->next;
		ft_printf("\n");
	}
}

void		ft_dump_env(t_env *env)
{
	ft_printf("prog_name = %s\n", env->prog_name);
	ft_printf("with flags :\n");
	ft_dump_flags(env);
	ft_dump_champs(env);
}
