/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:36:09 by toliver           #+#    #+#             */
/*   Updated: 2020/01/03 22:37:14 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_arena_error(int error)
{
	ft_dprintf(2, "%s: ", ft_get_env()->prog_name);
	if (error == NOT_ENOUGH_SPACE)
		ft_dprintf(2, "Not enough space in arena to place all champions\n");
	else if (error == NO_CHAMPIONS)
		ft_dprintf(2, "No champion or no working champion were given\n");
	else if (error == MALLOC_FAIL)
		ft_dprintf(2, "malloc failed : %s\n", strerror(errno));
	return (0);
}

void		ft_dump_arena(t_arena *arena)
{
	int			i;
	t_process	*ptr;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%.2x(%d) ", arena->arena[i].value, arena->arena[i].writer);
		i++;
	}
	ft_printf("\n");
	ptr = arena->process;
	while (ptr)
	{
		ft_printf("process:\n");
		ft_printf("\tpos = %d\n", ptr->pos);
		ft_printf("\topcode_value = %hhu\n", ptr->opcode_value);
		ft_printf("\tcycles to exec = %d\n", ptr->cycles_to_exec);
		ft_printf("\top size = %d\n", ptr->op_size);
		ft_printf("\tpid = %d\n", ptr->pid);
		ptr = ptr->next;
	}
}
