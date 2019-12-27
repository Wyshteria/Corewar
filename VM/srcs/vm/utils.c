/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 23:58:23 by toliver           #+#    #+#             */
/*   Updated: 2019/12/27 03:58:54 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_get_process_infos(t_process *process, t_arena *arena)
{
	process->opcode_value = arena->arena[process->pos].value;
	process->owner = arena->arena[process->pos].writer;
	if (process->opcode_value > 0 && process->opcode_value < 17)
	{
		process->cycles_to_exec = op_tab[process->opcode_value].cycles;
	}
	else
		process->cycles_to_exec = 1;
}

int			ft_add_process(t_arena *arena, int pos)
{
	t_process		*process;

	if (!(process = (t_process*)malloc(sizeof(t_process))))
		return (ft_arena_error(MALLOC_FAIL));
	ft_bzero(process, sizeof(t_process));
	process->pos = pos % MEM_SIZE;
	process->next = arena->process;
	arena->process = process;
	ft_get_process_infos(process, arena);
	process->pid = arena->pid;
	arena->pid += 1;
	return (1);
}

int			ft_clone_process(t_arena *arena, t_process *to_clone, int pos)
{
	t_process	*process;
	if (!(process = (t_process*)malloc(sizeof(t_process))))
	{
		ft_arena_error(MALLOC_FAIL);
		ft_free_env(ft_get_env());
		exit(-1);
		// verifier qunad meme
	}
	ft_memcpy(process, to_clone, sizeof(t_process));
	process->pos = (pos + to_clone->pos) % MEM_SIZE;
	if (process->pos < 0)
		process->pos = MEM_SIZE + process->pos;
	process->pid = arena->pid;
	process->live_number = 0;
	arena->pid += 1;
	process->next = arena->process;
	arena->process = process;
	process->need_refresh = 1;
	//ft_get_process_infos(process, arena);
	return (1);
}

void		ft_move_process(t_opcode *op, t_process *process, t_arena *arena)
{
	if (process->pos < 0)
		process->pos = MEM_SIZE + process->pos;
	if (op->opcode > 0 && op->opcode <= 16 && ft_verbose_flag(VERBOSE_PC_MOVEMENT_FLAG))
		ft_verbose_move(op, process, arena);
//	ft_printf("test %x %d %d\n", process->pos, op->size, op->opcode);
//	ft_dump_op(op);
	process->pos = (process->pos + op->size) % MEM_SIZE;
	process->need_refresh = 1;
//	ft_get_process_infos(process, arena);
}

void		ft_write_in_arena(t_arena *arena, int pos, int32_t value, int owner)
{
	union u_converter	converter;
	int					i;

	converter.real_value = ft_swap(value);
	i = 0;
//	ft_printf("pos %d value %d owner %d\n", pos, value, owner);
	if (pos < 0)
		pos = MEM_SIZE + pos;
	while (i < 4)
	{
		arena->arena[(pos + i) % MEM_SIZE].value = converter.value[i];
		arena->arena[(pos + i) % MEM_SIZE].writer = owner;
		i++;
	}	
}

int32_t			ft_parse_value(t_arena *arena, int pos, int size)
{
	union u_converter	value;
	int					i;

	i = 0;
	value.value[0] = 0;
	value.value[1] = 0;
	value.value[2] = 0;
	value.value[3] = 0;
	//value.real_value = 0;
	if (pos < 0)
		pos = MEM_SIZE + pos;
	while (i < size)
	{
		value.value[i] = arena->arena[((pos + i) % MEM_SIZE)].value;
		i++;
	}
	if (size == 4)
		value.real_value = ft_swap(value.real_value);
	else if (size == 2)
	{
		int			tmp = value.value[0];

		value.value[0] = value.value[1];
		value.value[1] = tmp;
	}
	return (value.real_value);	
}

int32_t		ft_get_value_from_address(t_arena *arena, int pos, int32_t offset)
{
	int					realpos;
	int32_t				value;

	realpos = (pos + offset) % MEM_SIZE;
	if (realpos < 0)
		realpos = MEM_SIZE + realpos;
	value = ft_parse_value(arena, realpos, REG_SIZE);
	return (value);
}

int32_t		ft_get_value_from(t_opcode *op, t_process *process, t_arena *arena, int num)
{
	int32_t	value;

	if (op->params_types[num] == T_REG)
		value = *(int32_t*)process->reg[op->params[num] - 1].mem;
	else if (op->params_types[num] == T_DIR)
		value = op->params[num];
	else
	{
		value = ft_get_value_from_address(arena, process->pos, op->params[num]);
//		ft_printf("faire le t_ind !\n");
		// ici parser et faire le swap
	}
	return (value);
}


uint32_t	ft_swap(uint32_t toswap)
{
	uint32_t	swapped;

	swapped = ((toswap>>24)&0xff) |
                    ((toswap<<8)&0xff0000) |
                    ((toswap>>8)&0xff00) |
                    ((toswap<<24)&0xff000000);
	return (swapped);
}

int			ft_is_containing_other_than(char *str, char *containing)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_one_of(str[i], containing))
			return (1);
		i++;
	}
	return (0);
}

int			ft_pow2(int pow)
{
	int		i;
	int		value;

	if (pow < 0)
		return (0);
	value = 1;
	i = 0;
	while (i < pow)
	{
		value *= 2;
		i++;
	}
	return (value);
}

int			ft_strchr_pos(char *str, int c)
{
	char	*val;

	val = ft_strchr(str, c);
	if (val == NULL)
		return (-1);
	return ((int)(val - str));
}

int			ft_is_one_of(char c, char *lookfor)
{
	int		i;
	
	i = 0;
	while (lookfor && lookfor[i])
	{
		if (lookfor[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void		*ft_malloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
	{
		ft_dprintf(2, "%s: Malloc failed: %s\n", ft_get_env()->prog_name, strerror(errno));
		ft_free_env(ft_get_env());
		exit(-1);
	}
	return (ptr);
}
