/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:18 by toliver           #+#    #+#             */
/*   Updated: 2019/12/09 17:23:28 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_arena_error(int error)
{
	ft_dprintf(2, "%s: ", ft_get_env()->prog_name);
	if (error == NOT_ENOUGH_SPACE)
		ft_dprintf(2, "Not enough space in arena to place all champions\n");
	return (0);
}


void			ft_dump_arena(t_arena *arena)
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
		ptr = ptr->next;
	}
}

int			ft_op_size(t_process *process, t_arena *arena)
{
	int		index;
	int		size;
	int		i;
	int		param_type;

	size = 0;
	if (op_tab[process->opcode_value].need_encoding_byte)
	{
		size += 1;
		index = (process->pos + 1) % MEM_SIZE;
		i = 0;
		while (i < op_tab[process->opcode_value].params_number)
		{
			param_type = ((arena->arena[index].value & (0b11000000 >> (i * 2)))	 >> (6 - (i * 2)));
			if (param_type == T_REG)
			   size += 1;
			else if (param_type == T_DIR)
				size += (op_tab[process->opcode_value].t_dir_is_two_bytes ? 2 : 4);
			else if (param_type == T_IND)
				size += IND_SIZE;
			i++;
		}
	}
	else
		size += (op_tab[process->opcode_value].t_dir_is_two_bytes ? 2 : 4);
	return (size);
}

void		ft_get_process_infos(t_process *process, t_arena *arena)
{
	process->opcode_value = arena->arena[process->pos].value;
//	process->op_size = 1;
	if (process->opcode_value > 0 && process->opcode_value < 17)
	{
		process->cycles_to_exec = op_tab[process->opcode_value].cycles;
//		process->op_size += ft_op_size(process, arena);
	}
	else
		process->cycles_to_exec = 0;
}

int			ft_add_process(t_arena *arena, int owner, int pos)
{
	t_process		*process;

	(void)owner;
	if (!(process = (t_process*)malloc(sizeof(t_process))))
		return (ft_arena_error(MALLOC_FAIL));
	ft_bzero(process, sizeof(t_process));
	process->pos = pos;
	process->next = arena->process;
	*((uint32_t*)(&process->reg[0].mem)) = owner;
	arena->process = process;
	ft_get_process_infos(process, arena);
	return (1);
}

void		ft_fill_arena(t_arena *arena, t_champ *champ, int pos)
{
	int		i;

	i = 0;
	while (i < (int)champ->header.prog_size)
	{
		arena->arena[pos + i].value = champ->content[i];
		arena->arena[pos + i].writer = champ->number;
		i++;
	}
}

int			ft_init_process(t_env *env, int space_between)
{
	t_champ	*ptr;
	int				actualpos;

	actualpos = 0;
	ptr = env->champs;
	while (ptr)
	{
		ft_fill_arena(&env->arena, ptr, actualpos);
		if (!(ft_add_process(&env->arena, ptr->number, actualpos)))
			return (0);
		actualpos += space_between;
		ptr = ptr->next;
	}
	return (1);
}


int			ft_init_arena(t_env *env)
{
	unsigned int	total_size;
	t_champ			*ptr;
	int				champ_number;
	int				space_between;

	ptr = env->champs;
	total_size = 0;
	champ_number = 0;
	while (ptr)
	{
		total_size += ptr->header.prog_size;
		champ_number++;
		ptr = ptr->next;
	}
	if (total_size >= MEM_SIZE)
		return (ft_arena_error(NOT_ENOUGH_SPACE)); 
	space_between = MEM_SIZE / champ_number;
	ptr = env->champs;
	if (!ft_init_process(env, space_between))
		return (0);
	ft_dump_arena(&env->arena);
	return (1);
}

int			main(int ac, char **av)
{
	t_env	env;

	ft_env_init(&env, av[0], ac - 1);
	if (!ft_parse_params(&env, av + 1))
		return (-1);
	ft_parse_champs(&env);
	// verifier qu'il y a bien un champion et qu'on en a pas trop
	if (ft_init_arena(&env))
		ft_visu(&env);
	//	ft_dump_env(&env);
	ft_free_env(&env);
	return (0);
}

// penser a set les numeros de players en negatif
