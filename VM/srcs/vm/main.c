/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:18 by toliver           #+#    #+#             */
/*   Updated: 2019/12/07 19:50:27 by toliver          ###   ########.fr       */
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
	if (ptr->next)
		tmp = ptr->next->next;
	else
		tmp = NULL;
	ft_free_champ(champ);
	ptr->next = tmp;
}

/*
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
*/
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
	else if (error == NAME_TOO_LONG)
		ft_dprintf(2, "Champ name is too long, max size : %d\n", PROG_NAME_LENGTH);
	else if (error == COMMENT_TOO_LONG)
		ft_dprintf(2, "Champ comment is too long, max size : %d\n", COMMENT_LENGTH);
	else if (error == SIZE_ERROR)
		ft_dprintf(2, "Champ size do not match given size: %u\n", champ->header.prog_size);
	return (0);
}

int			ft_parse_magic(t_env *env, t_champ *champ)
{
	int		retval;

	retval = read(champ->fd, &(champ->header.magic), sizeof(uint32_t));
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
	int		i;

	retval = read(champ->fd, &(champ->header.prog_name), PROG_NAME_LENGTH + 1);
	if (retval == -1)
		return (ft_champ_error(env, READ_ERROR, champ));
	else if (retval == 0 || retval != PROG_NAME_LENGTH + 1)
		return (ft_champ_error(env, TOO_SHORT, champ));
	champ->header.prog_name[retval] = '\0';
	i = 0;
	while (i < PROG_NAME_LENGTH + 1 && champ->header.prog_name[i])
		i++;
	if (i == PROG_NAME_LENGTH + 1 && champ->header.prog_name[i])
		return (ft_champ_error(env, NAME_TOO_LONG, champ));



	if ((PROG_NAME_LENGTH + 1) & 3)
	{
		char buffer[12];
		read(champ->fd, buffer, 4 - ((PROG_NAME_LENGTH + 1) & 3));
	}
	return (1);	
}

int			ft_parse_size(t_env *env, t_champ *champ)
{
	int		retval;

	retval = read(champ->fd, &(champ->header.prog_size), sizeof(uint32_t));
	if (retval == -1)
		return (ft_champ_error(env, READ_ERROR, champ));
	else if (retval == 0)
		return (ft_champ_error(env, TOO_SHORT, champ));
	champ->header.prog_size = ft_swap(champ->header.prog_size);
	return (1);	
}

int			ft_parse_comment(t_env *env, t_champ *champ)
{
	int		retval;
	int		i;

	retval = read(champ->fd, &(champ->header.comment), COMMENT_LENGTH + 1);
	if (retval == -1)
		return (ft_champ_error(env, READ_ERROR, champ));
	else if (retval == 0 || retval != COMMENT_LENGTH + 1)
		return (ft_champ_error(env, TOO_SHORT, champ));
	champ->header.comment[retval] = '\0';
	i = 0;
	while (i < COMMENT_LENGTH + 1 && champ->header.comment[i])
		i++;
	if (i == COMMENT_LENGTH + 1 && champ->header.comment[i])
		return (ft_champ_error(env, COMMENT_TOO_LONG, champ));



	if ((COMMENT_LENGTH + 1) & 3)
	{
		char buffer[12];
		read(champ->fd, buffer, 4 - ((COMMENT_LENGTH + 1) & 3));
	}
	return (1);	
}


int			ft_parse_champ(t_env *env, t_champ *champ)
{

	if (champ->fd == -1)
		return (ft_champ_error(env, READ_ERROR, champ));
	if (!(ft_parse_magic(env, champ)))
		return (0);
	if (!(ft_parse_name(env, champ)))
		return (0);
	if (!(ft_parse_size(env, champ)))
		return (0);
	if (!(ft_parse_comment(env, champ)))
		return (0);
	champ->offset = lseek(champ->fd, 0, SEEK_CUR);
	if (lseek(champ->fd, 0, SEEK_END) - champ->offset != champ->header.prog_size)
		return (ft_champ_error(env, SIZE_ERROR, champ));
	champ->offset = lseek(champ->fd, champ->offset, SEEK_SET);
	champ->content = (char*)ft_malloc(champ->header.prog_size);
	read(champ->fd, champ->content, champ->header.prog_size);




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
