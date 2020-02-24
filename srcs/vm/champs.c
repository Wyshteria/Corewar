/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jates- <jates-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 22:34:31 by toliver           #+#    #+#             */
/*   Updated: 2020/02/24 17:23:12 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ft_parse_name(t_env *env, t_champ *champ)
{
	int		retval;
	int		i;
	char	buffer[12];

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
		read(champ->fd, buffer, 4 - ((PROG_NAME_LENGTH + 1) & 3));
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
	char	buffer[12];

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
		read(champ->fd, buffer, 4 - ((COMMENT_LENGTH + 1) & 3));
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
	if (lseek(champ->fd, 0, SEEK_END) - champ->offset != champ->header.prog_size
			|| champ->header.prog_size > CHAMP_MAX_SIZE)
		return (ft_champ_error(env, SIZE_ERROR, champ));
	champ->offset = lseek(champ->fd, champ->offset, SEEK_SET);
	champ->content = (char*)ft_safe_malloc(champ->header.prog_size);
	read(champ->fd, champ->content, champ->header.prog_size);
	return (1);
}

void		ft_parse_champs(t_env *env)
{
	t_champ		*ptr;
	t_champ		*tmp;
	uint32_t	number;

	ptr = env->champs;
	number = 1;
	while (ptr)
	{
		if (!ft_parse_champ(env, ptr))
		{
			tmp = ptr->next;
			ft_delete_champ(env, ptr);
			ptr = tmp;
		}
		else if (ptr->hasnumber == 0)
		{
			while (ft_get_champ(-number))
				number++;
			ptr->number = -number;
			ptr = ptr->next;
			number++;
		}
		else
			ptr = ptr->next;
	}
}
