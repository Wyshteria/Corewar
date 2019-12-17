/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jates- <jates-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 03:10:28 by jates-            #+#    #+#             */
/*   Updated: 2019/12/17 06:38:24 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <errno.h>
#include <string.h>

static char	*cor_filename(t_env *env, t_file *file)
{
	const int	len = ft_strlen(file->filename);
	char		*corname;

	corname = NULL;
	if (len > 2 && file->filename[len - 2] == '.'
	&& file->filename[len - 1] == 's' && file->filename[len] == 0)
		if ((corname = ft_strnew(len + 2)) 
		&& ft_strncpy(corname, file->filename, len - 1))
			return(ft_strcat(corname, "cor");
	else
		if ((corname = ft_strnew(len + 4)) 
		&& ft_strncpy(corname, file->filename, len))
			return (ft_strcat(corname, ".cor");		
	ft_error(env, file, MALLOC_FAIL);
	return (corname);
}

void	write_hexlen(int fd, size_t size, int len)
{
	unsigned char	*tmp;
	int				i;

	i = len;
	if (!(tmp = (unsigned char*)ft_memalloc(i * sizeof(unsigned char))))
		return ;
	while (size && i > 0)
	{
		tmp[--i] = size % 256;
		size /= 256;
	}
	write(fd, tmp, len);
	ft_memdel((void**)&tmp);
}

int	ft_write_head(t_env *env, t_file *file)
{
	disp_hexlen(fd, COREWAR_EXEC_MAGIC, 4);
	write(fd, champ->name, PROG_NAME_LENGTH);
	disp_hexlen(fd, champ->accu_len, 8);
	write(fd, champ->comment, COMMENT_LENGTH);
	write(fd, "\0\0\0\0", 4);
	t = champ->inst;
	while (t)
	{
		write_inst(fd, (t_inst *)t->content, champ->labels);
		t = t->next;
	}
}

int	ft_init_prog(t_env *env, t_file *file)
{
	t_program	champ;
	t_token 	*tmp;

	ft_bzero(&champ, sizeof(t_program));
		tmp = file->tokens;
	if (!(tmp->type == COMMAND && ft_strnequ(tmp->value, "name", 5))
		return(ft_lexical_error(tmp);
	else if (!(tmp->next && tmp->type == STRING 
		&& ft_memchr((void *)tmp->value, 0, PROG_NAME_LENGTH)))
		return(ft_lexical_error(tmp);
	
	if (!(champ.filename = ft_cor_filename(env, file)))
		return (0);
	if ((champ.fd = open(champ.filename, O_WRONLY | O_CREAT, 0755) < 0))
	{	
		free(champ.filename);
		return (ft_error(env, file, OPEN_ERROR));
	}
	 

}


int	ft_write_corfile(t_env *env, t_file *file)
{
	char 
	int const fd = open(file->name, }

:w
