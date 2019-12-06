/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:18 by toliver           #+#    #+#             */
/*   Updated: 2019/12/06 07:26:05 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_delete_champ(t_env *env, t_champ *champ)
{
	t_champ	*ptr;
	t_champ	*tmp;

	if (env->champs == champ)
		env->champs = champ->next;
	ptr = env->champs;
	while (ptr->next && ptr->next != champ)
		ptr = ptr->next;
	tmp = ptr->next->next;
	ft_free_champ(champ);
	ptr->next = tmp;
}


void		ft_read_error(t_champ *champ)
{
	ft_dprintf(2, "Couldn't read file %s : %s\n", champ->filename, strerror(errno));
}

void		ft_open_error(t_champ *champ)
{
	ft_dprintf(2, "Couldn't open file %s : %s\n", champ->filename, strerror(errno));
}

void		ft_lseek_error(t_env *env, t_champ *champ)
{
	(void)champ;
	ft_dprintf(2, "%s: lseek failed: %s\n", env->prog_name, strerror(errno));
}

int			ft_offset_head(t_env *env, t_champ *champ, size_t size)
{
	champ->offset = lseek(champ->fd, champ->offset + size, SEEK_SET);
	if (champ->offset == -1)
	{
		ft_lseek_error(env, champ);
		return (0);
	}
	return (1);
}

int			ft_parse_str(t_champ *champ, char **line)
{
	char	buf[51];
	int		i;
	int		size;
	int		retval;

	size = 0;
	while ((retval = read(champ->fd, buf, 50)) > 0)
	{
		i = 0;
		while(i < retval && buf[i])
			i++;
		size += i;
		if (i != retval)
			break;
	}
	if (retval == -1)
	{
		ft_read_error(champ);
		return (0);
	}
	*line = (char*)ft_malloc(sizeof(char) * (size + 1));
	ft_offset_head(ft_get_env(), champ, 0);
	retval = read(champ->fd, *line, size);
	if (retval == -1)
	{
		free(*line);
		*line = NULL;
//		ft_malloc_fail(ft_get_env());
		return (0);
	}
	(*line)[retval] = '\0';
	ft_offset_head(ft_get_env(), champ, 0);
	return (1);
}

int			ft_champ_error(t_env *env, int error, t_champ *champ)
{
	ft_dprintf(2, "%s: %s: ", env->prog_name, champ->filename);
	if (error == OPEN_ERROR)
		ft_dprintf(2, "Couldn't open the file: %s\n", strerror(errno));
	else if (error == READ_ERROR)
		ft_dprintf(2, "Couldn't read the file: %s\n", strerror(errno));
	else if (error == TOO_SHORT)
		ft_dprintf(2, "Reading the file ended too soon\n");
	else if (error == MAGIC_ERROR)
		ft_dprintf(2, "File is not a core-war champion\n");
	return (0);
}

int			ft_parse_magic(t_env *env, t_champ *champ)
{
	int		retval;

	retval = read(champ->fd, &(champ->header.magic), 4);
	if (retval == -1)
		return (ft_champ_error(env, READ_ERROR, champ));
	else if (retval == 0)
		return (ft_champ_error(env, TOO_SHORT, champ));
	champ->header.magic = ft_swap(champ->header.magic);
	if (champ->header.magic != COREWAR_EXEC_MAGIC)
		return (ft_champ_error(env, MAGIC_ERROR, champ));
	champ->offset = 4;
	return (1);	
}

int			ft_parse_name(t_env *env, t_champ *champ)
{
int		retval;

	retval = read(champ->fd, &(champ->header.prog_name), PROG_NAME_LENGTH);
	if (retval == -1)
		return (ft_champ_error(env, READ_ERROR, champ));
	else if (retval == 0 || retval != 128)
		return (ft_champ_error(env, TOO_SHORT, champ));
	char buffer[12];
	read(champ->fd, buffer, 8);		// TKT CA MARCHE
	write(1, buffer, 8);
	return (1);	
}

int			ft_parse_champ(t_env *env, t_champ *champ)
{

	if (champ->fd == -1)
	{
		ft_champ_error(env, READ_ERROR, champ);
		return (0);
	}
	if (!(ft_parse_magic(env, champ)))
		return (0);
	if (!(ft_parse_name(env, champ)))
		return (0);
	read(champ->fd, champ->header.comment, COMMENT_LENGTH);
	/*
	read(champ->fd, &(champ->header), sizeof(t_header));
	champ->header.magic = ft_swap(champ->header.magic);
	champ->header.prog_size = ft_swap(champ->header.prog_size);
	*/
	/*
	   check magic, len name, len comm (on cherche le /0)
	if (!ft_parse_magic(champ))
		return (0);
	if (!ft_parse_name(champ))
		return (0);
	if (!ft_parse_prog_size(champ))
		return (0);
		*/
//	if (!ft_parse_comment(champ))
//		return (0);	
//	champ->header.prog_size = ft_swap(champ->header.prog_size);
	// verifier que le prog name et le prog comment soient de la bonne taille
	return (1);
}

void		ft_parse_champs(t_env *env)
{
	t_champ	*ptr;
	t_champ	*tmp;

	ptr = env->champs;
	while (ptr)
	{
		if (!ft_parse_champ(env, ptr))
		{
			tmp = ptr->next;
			ft_delete_champ(env, ptr);
			ptr = tmp;
		}
		else
			ptr = ptr->next;
	}
}

int			main(int ac, char **av)
{
	t_env	env;

	ft_env_init(&env, av[0], ac - 1);
	if (!ft_parse_params(&env, av + 1))
		return (-1);
	ft_parse_champs(&env);
	ft_dump_env(&env);
	ft_free_env(&env);
	return (0);
}
