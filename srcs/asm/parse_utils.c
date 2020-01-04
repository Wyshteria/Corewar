/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboukrou <lboukrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:48:43 by toliver           #+#    #+#             */
/*   Updated: 2020/01/04 04:04:29 by lboukrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token		*ft_last_token(t_file *file)
{
	t_token *token;

	token = file->tokens;
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

int			ft_offset_head(t_env *env, t_file *file, size_t size)
{
	file->offset = lseek(file->fd, file->offset + size, SEEK_SET);
	if (file->offset == -1)
	{
		ft_error(env, file, LSEEK_ERROR);
		return (0);
	}
	return (1);
}

int			ft_offset_lines(t_env *env, t_file *file, char *str)
{
	int		i;

	i = 0;
	(void)env;
	while (str && str[i])
	{
		if (str[i] == NEWLINE_CHAR)
		{
			file->line += 1;
			file->col = 1;
		}
		else
			file->col += 1;
		i++;
	}
	return (1);
}

void		ft_skip_spaces(t_env *env, t_file *file)
{
	int		size;
	int		i;
	char	buffer[51];
	int		retval;

	size = 0;
	while ((retval = read(file->fd, buffer, 50)) > 0)
	{
		buffer[retval] = '\0';
		i = 0;
		while (buffer[i] && (buffer[i] == ' ' || buffer[i] == '\t'))
		{
			file->col += 1;
			i++;
		}
		size += i;
		if (i != retval)
			break ;
	}
	if (retval == -1)
		ft_error(env, file, READ_ERROR);
	else if (retval == 0)
		file->mode = DONE;
	else
		ft_offset_head(env, file, size);
}

// static int	read_file_fd(t_file *file, char *containing, char *buf)
// {
// 	int		retval;
// 	int		size;
// 	int		i;

// 	size = 0;
// 	while ((retval = read(file->fd, buf, 50)) > 0)
// 	{
// 		i = 0;
// 		buf[retval] = '\0';
// 		while (buf[i] && ft_is_one_of(buf[i], containing))
// 			i++;
// 		size += i;
// 		if (i != retval)
// 			break ;
// 	}
// 	if (retval == -1)
// 		return (-1);
// 	if (retval == 0)
// 		file->mode = DONE;
// 	return (size);
// }

int			ft_parse_while(t_file *file, char *containing, char **line)
{
	char	buf[51];
	int		i;
	int		size;
	int		retval;

	// if ((size = read_file_fd(file, containing, buf)) == -1)
	// 	return (ft_error(ft_get_env(), file, READ_ERROR));
	size = 0;
	while ((retval = read(file->fd, buf, 50)) > 0)
	{
		i = 0;
		buf[retval] = '\0';
		while (buf[i] && ft_is_one_of(buf[i], containing))
			i++;
		size += i;
		if (i != retval)
			break ;
	}
	if (retval == -1)
		return (ft_error(ft_get_env(), file, READ_ERROR));
	if (retval == 0)
		file->mode = DONE;
	*line = (char*)ft_malloc(sizeof(char) * (size + 1));
	ft_offset_head(ft_get_env(), file, 0);
	retval = read(file->fd, *line, size);
	if (retval == -1)
	{
		free(*line);
		*line = NULL;
		return (ft_error(ft_get_env(), file, READ_ERROR));
	}
	(*line)[retval] = '\0';
	ft_offset_head(ft_get_env(), file, size);
	ft_offset_lines(ft_get_env(), file, *line);
	return (1);
}

int			ft_parse_until(t_file *file, char *limit, char **line, int skipping)
{
	char	buf[51];
	int		i;
	int		size;
	int		retval;
	char	end;

	size = 0;
	while ((retval = read(file->fd, buf, 50)) > 0)
	{
		i = 0;
		buf[retval] = '\0';
		while (buf[i] && !(end = ft_is_one_of(buf[i], limit)))
			i++;
		size += i;
		if (i != retval)
			break ;
	}
	if (retval == -1)
		return (ft_error(ft_get_env(), file, READ_ERROR));
	if (retval == 0)
		file->mode = DONE;
	*line = (char*)ft_malloc(sizeof(char) * (size + 1));
	ft_offset_head(ft_get_env(), file, 0);
	retval = read(file->fd, *line, size);
	if (retval == -1)
	{
		free(*line);
		*line = NULL;
		return (ft_error(ft_get_env(), file, READ_ERROR));
	}
	(*line)[retval] = '\0';
	ft_offset_head(ft_get_env(), file, size + (skipping ? 1 : 0));
	ft_offset_lines(ft_get_env(), file, *line);
	if (end && skipping)
		ft_offset_lines(ft_get_env(), file, ((char[]){end, '\0'}));
	return (1);
}
