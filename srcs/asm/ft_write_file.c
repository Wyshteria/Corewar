/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jates- <jates-@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 03:10:28 by jates-            #+#    #+#             */
/*   Updated: 2019/12/20 01:03:13 by jates-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"



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

void	ft_write_head(t_program *prog)
{
	write_hexlen(prog->fd, COREWAR_EXEC_MAGIC, 4);
	write(prog->fd, prog->header.prog_name, PROG_NAME_LENGTH);
	write_hexlen(prog->fd, prog->header.prog_size, 8);
	write(prog->fd, prog->header.comment, COMMENT_LENGTH);
	write(prog->fd, "\0\0\0\0", 4);
}

void	ft_write_body(t_program *prog, t_operation *op)
{
	int			i;
	int			nbr = -1;

	ft_dump_op(prog);
	while (op && nbr--)
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
				write_hexlen(prog->fd, op->params[i].int_value, op->params[i].len);
			i++;
		}
		op = op->next;
	}
}

int	ft_open_cor_file(t_program *prog, t_env *env, t_file *file)
{
	if ((prog->fd = open(prog->filename, O_WRONLY | O_CREAT, 0755)) < 0)
	{
		ft_clear_prog(prog);
		return (ft_error(env, file, OPEN_ERROR));
	}
	else
		ft_dump_prog(&env->prog);
	ft_write_head(prog);
	ft_write_body(prog, prog->operations);
	close(prog->fd);
	return (1);
}


