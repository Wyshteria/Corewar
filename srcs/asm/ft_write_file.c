/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboukrou <lboukrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 03:10:28 by jates-            #+#    #+#             */
/*   Updated: 2020/01/05 01:10:00 by lboukrou         ###   ########.fr       */
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
		return ;
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
	write_hexlen(prog->fd, prog->header.magic, 4);
	write(prog->fd, prog->header.prog_name, PROG_NAME_LENGTH);
	write_hexlen(prog->fd, prog->header.prog_size, 8);
	write(prog->fd, prog->header.comment, COMMENT_LENGTH);
	write(prog->fd, "\0\0\0\0", 4);
	return (1);
}

static void	ft_write_body(t_program *prog, t_operation *op)
{
	int			i;

	// ft_dump_op(prog);
	while (op)
	{
		write_hexlen(prog->fd, op->opc, 1);
		if (op->is_encoding_needed)
			write_hexlen(prog->fd, op->encoding, 1);
		i = 0;
		while (i < op->p_num)
		{
			if (op->params[i].value_type == REGISTER)
				write_hexlen(prog->fd, op->params[i].int_value, 1);
			else
				write_hexlen(prog->fd, op->params[i].int_value, \
					op->params[i].len);
			i++;
		}
		op = op->next;
	}
}

int		ft_open_cor_file(t_program *prog, t_env *env, t_file *file)
{
	if ((prog->fd = open(prog->filename, O_WRONLY | O_CREAT, 0755)) < 0)
	{
		ft_clear_prog(prog);
		return (ft_error(env, file, OPEN_ERROR));
	}
	// else
	// 	ft_dump_prog(&env->prog);
	ft_write_head(prog);
	ft_write_body(prog, prog->operations);
	close(prog->fd);
	return (1);
}
