#include "asm.h"

static t_program	**ft_get_progptr(void)
{
	static t_program	*prog = NULL;

	return (&prog);
}

t_program		*ft_get_prog(void)
{
	return (*(ft_get_progptr()));
}

void		ft_set_prog(t_program *prog)
{
	*(ft_get_progptr()) = prog;
}

void		ft_init_prog(t_program *prog)
{
	ft_bzero(prog, sizeof(t_program));
}

void		ft_free_prog(t_program *prog)
{
	if (prog)
	{
		ft_free_op(prog->operations);
		ft_free_label(prog->label);
		free(prog->filename);
	}
}