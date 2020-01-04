/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champs1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 01:16:00 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 01:58:28 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_delete_champ(t_env *env, t_champ *champ)
{
	t_champ	*ptr;
	t_champ	*tmp;

	if (env->champs == champ)
		env->champs = champ->next;
	else
	{
		ptr = env->champs;
		while (ptr->next && ptr->next != champ)
			ptr = ptr->next;
		if (ptr->next)
			tmp = ptr->next->next;
		else
			tmp = NULL;
		ptr->next = tmp;
	}
	ft_free_champ(champ);
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
	else if (error == NAME_TOO_LONG)
		ft_dprintf(2, "Champ name is too long, max size : %d\n",
				PROG_NAME_LENGTH);
	else if (error == COMMENT_TOO_LONG)
		ft_dprintf(2, "Champ comment is too long, max size : %d\n",
				COMMENT_LENGTH);
	else if (error == SIZE_ERROR)
		ft_dprintf(2, "Champ size do not match given size: %u\n",
				champ->header.prog_size);
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
