/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboukrou <lboukrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 03:10:28 by jates-            #+#    #+#             */
/*   Updated: 2020/01/05 01:54:08 by lboukrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	write_hexlen(int fd, size_t size, int len)
{
	unsigned char	*tmp;
	int				i;
	int				ret;

	i = len;
	if (!(tmp = (unsigned char*)ft_memalloc(i * sizeof(unsigned char))))
		return (-1);
	while (size && i > 0)
	{
		tmp[--i] = size % 256;
		size /= 256;
	}
	ret = write(fd, tmp, len);
	ft_memdel((void**)&tmp);
	if (ret == -1)
		return (-1);
	else if (ret != len)
		return (0);
	return (1);
}

static int	ft_write_head(t_program *prog)
{
	int		ret;
	int		mark;

	mark = 0;
	if ((ret = write_hexlen(prog->fd, prog->header.magic, 4)) == -1)
		return (ret);
	else if (ret == 0)
		mark++;
	if ((ret = write(prog->fd, prog->header.prog_name, PROG_NAME_LENGTH)) == -1)
		return (ret);
	else if (ret == 0)
		mark++;
	if ((ret = write_hexlen(prog->fd, prog->header.prog_size, 8)) == -1)
		return (ret);
	else if (ret == 0)
		mark++;
	if ((ret = write(prog->fd, prog->header.comment, COMMENT_LENGTH)) == -1)
		return (ret);
	else if (ret == 0)
		mark++;
	if ((ret = write(prog->fd, "\0\0\0\0", 4)) == -1)
		return (ret);
	else if (ret == 0)
		mark++;
	return ((mark) ? 0 : 1);
}

static int	ft_write_while(t_program *prog, t_operation *op, int limit)
{
	int		i;
	int		ret;
	int		mark;
	
	i = 0;
	mark = 0;
	while (i < limit)
	{
		if (op->params[i].value_type == REGISTER)
		{	
			if ((ret = write_hexlen(prog->fd, op->params[i].int_value, 1)) == -1)
				return (-1);
			else if (ret == 0)
				mark++; 
		}
		else
		{
			if ((ret = write_hexlen(prog->fd, op->params[i].int_value,
									op->params[i].len)) == -1)
				return (-1);
			else if (ret == 0)
				mark++;
		}
		i++;
	}
	return (mark ? 0 : 1);
}

static int	ft_write_body(t_program *prog, t_operation *op)
{
	int			mark;
	int			ret;

	// ft_dump_op(prog);
	mark = 0;
	while (op)
	{
		if ((ret = write_hexlen(prog->fd, op->opc, 1)) == -1)
			return (ret);
		else if (ret == 0)
			mark++;
		if (op->is_encoding_needed)
		{
			if ((ret = write_hexlen(prog->fd, op->encoding, 1)) == -1)
				return (ret);
			else if (ret == 0)
				mark++;
		}
		if ((ret = ft_write_while(prog, op, op->p_num)) == -1)
			return (-1);
		else if (ret == 0)
			mark++;
		op = op->next;
	}
	return (mark ? 0 : 1);
}

int		ft_open_cor_file(t_program *prog, t_env *env, t_file *file)
{
	int		ret;
	int		mark;
	
	mark = 0;
	if ((prog->fd = open(prog->filename, O_WRONLY | O_CREAT, 0755)) < 0)
	{
		ft_clear_prog(prog);
		return (ft_error(env, file, OPEN_ERROR));
	}
	// else
	// 	ft_dump_prog(&env->prog);
	if ((ret = ft_write_head(prog)) == -1)
		return (ft_error(env, file, WRITE_ERROR));
	else if (ret == 0)
		mark++; //TODO Afficher corrompu, how ?
	if ((ret = ft_write_body(prog, prog->operations)) == -1)
		return (ft_error(env, file, WRITE_ERROR));
	else if (ret == 0)
		mark++;			
	close(prog->fd);
	return (mark ? -1 : 1);
}
