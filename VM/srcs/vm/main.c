/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:18 by toliver           #+#    #+#             */
/*   Updated: 2019/12/04 20:24:49 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_env		**ft_get_envptr(void)
{
	static t_env	*env = NULL;

	return (&env);
}

t_env		*ft_get_env(void)
{
	return (*(ft_get_envptr()));
}

void		ft_set_env(t_env *env)
{
	*(ft_get_envptr()) = env;
}


void		ft_free_champ(t_champ *champ)
{
	free(champ->content);
	free(champ);
}

void		ft_free_champs(t_env *env)
{
	t_champ	*ptr;
	t_champ	*tmp;

	ptr = env->champs;
	while (ptr)
	{
		tmp = ptr->next;
		ft_free_champ(ptr);
		ptr = tmp;;
	}
	env->champs = NULL;
}

int			ft_is_one_of(char c, char *lookfor)
{
	int		i;
	
	i = 0;
	while (lookfor && lookfor[i])
	{
		if (lookfor[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void		ft_read_error(t_champ *champ)
{
	ft_dprintf(2, "Couldn't read file %s : %s\n", champ->filename, strerror(errno));
}

void		ft_open_error(t_champ *champ)
{
	ft_dprintf(2, "Couldn't open file %s : %s\n", champ->filename, strerror(errno));
}

void		ft_free_env(t_env *env)
{
	ft_free_champs(env);
}

void		ft_malloc_fail(t_env *env)
{
	ft_dprintf(2, "%s: Malloc failed: %s\n", env->prog_name, strerror(errno));
}


void		*ft_malloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
	{
		ft_malloc_fail(ft_get_env());
		ft_free_env(ft_get_env());
		exit(-1);
	}
	return (ptr);
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
		ft_malloc_fail(ft_get_env());
		return (0);
	}
	(*line)[retval] = '\0';
	ft_offset_head(ft_get_env(), champ, 0);
	return (1);
}

void		ft_init_env(t_env *env, char *prog_name)
{
	ft_bzero(env, sizeof(t_env));
	env->prog_name = prog_name;	
}

int			ft_pow2(int pow)
{
	int		i;
	int		value;

	if (pow < 0)
		return (0);
	value = 1;
	i = 0;
	while (i < pow)
	{
		value *= 2;
		i++;
	}
	return (value);
}

int			ft_strchr_pos(char *str, int c)
{
	char	*val;

	val = ft_strchr(str, c);
	if (val == NULL)
		return (-1);
	return ((int)(val - str));
}

void			ft_usage(t_env *env)
{
	ft_dprintf(2, "usage: %s [-a] [[-d N] [-s N] [-v N]] champion.cor ...\n", env->prog_name);
	exit(-1);
}

void		ft_param_flags_wrong(t_env *env, char c)
{
	ft_dprintf(2, "%s: Can't have a flag after the parameter needing flag : %c\n", env->prog_name, c);
	exit(-1);
}

void		ft_unknown_flag(t_env *env, char c)
{
	ft_dprintf(2, "%s: Illegal option -- %c\n", env->prog_name, c);
	ft_usage(env);
}

void		ft_negative_param(int number, t_env *env)
{
	ft_dprintf(2, "%s: Illegal negative argument : %d\n", env->prog_name, number);
	exit(-1);
}

void		ft_missing_param(t_env *env, char flag)
{
	ft_dprintf(2, "%s: missing argument after flag : %c\n", env->prog_name, flag);
	exit(-1);
}

int			ft_is_containing_other_than(char *str, char *containing)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_one_of(str[i], containing))
			return (1);
		i++;
	}
	return (0);
}

void		ft_parse_param_flag_parameter(t_env *env, char **av, int *i, char flag)
{
	int		number;

	if (*i >= env->ac)
		ft_missing_param(env, flag);
 	if (ft_is_containing_other_than(av[*i], "+-0123456789"))
		ft_missing_param(env, flag);
	number = ft_atoi(av[*i]);
	if (number < 0)
		ft_negative_param(number, env);
	if (flag == 'd')
		env->dump_cycles = number;
	else if (flag == 's')
		env->cycle_dump_cycles = number;
	else if (flag== 'v')
		env->verbose_level |= number;
}

void		ft_parse_flag(t_env *env, char **av, int *i, int *mode)
{
	int		j;

	if ((av[*i][0] == '-' && av[*i][1] == '-' && av[*i][2] == 0) || av[*i][0] != '-')
	{
		*mode = PARSE_FILES;
		if (av[*i][0] == '-')
			*i += 1;
	}
	else if (av[*i][0] == '-')
	{
		j = 1;
		while (ft_is_one_of(av[*i][j], CONCATABLE_FLAGS))
		{
			env->flags |= ft_pow2(ft_strchr_pos(CONCATABLE_FLAGS, av[*i][j]));
			j++;
		}
		if (ft_is_one_of(av[*i][j], PARAMS_FLAGS))
		{
			env->flags |= ft_pow2(ft_strchr_pos(PARAMS_FLAGS, av[*i][j]) + ft_strlen(CONCATABLE_FLAGS));
			if (av[*i][j + 1] != '\0')
				ft_param_flags_wrong(env, av[*i][j]);
			*i += 1;
			ft_parse_param_flag_parameter(env, av, i, av[*i - 1][j]);
		}
		else if (av[*i][j] != '\0')
			ft_unknown_flag(env, av[*i][j]);
		*i += 1;
	}
}

void		ft_add_champ(t_env *env, t_champ *champ)
{
	t_champ	*ptr;
	if (env->champs == NULL)
		env->champs = champ;
	else
	{
		ptr = env->champs;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = champ;
	}
}

void		ft_parse_files(t_env *env, char *filename)
{
	t_champ	champ;
	t_champ	*node;

	(void)env;
	ft_bzero(&champ, sizeof(t_champ));
	champ.filename = filename;
	champ.fd = open(filename, O_RDONLY);
	node = (t_champ*)ft_malloc(sizeof(t_champ));
	ft_memcpy(node, &champ, sizeof(t_champ));
	ft_add_champ(env, node);
	// ICI MALLOC LA LISTE CHAINEE et memcpy cette variable et l'ajouter a la fin de la liste de env 
}

int			ft_parse_params(t_env *env, int ac, char **av)
{
	int		i;
	int		mode;


	i = 0;
	mode = PARSE_FLAGS;
	if (ac == 0)
		ft_usage(env);
	while (i < ac && mode != PARSE_ERROR && mode != PARSE_CRASH)
	{
		while (mode == PARSE_FLAGS && i < ac)
			ft_parse_flag(env, av, &i, &mode);
		if (mode == PARSE_FILES)
		{
			ft_parse_files(env, av[i]);
			i++;
		}
	}
	return (1);
}

int			ft_env_init(t_env *env, char *progname, int ac)
{

	ft_bzero(env, sizeof(t_env));
	env->prog_name = progname;
	env->ac = ac;
	ft_set_env(env);
	return (1);
}

void		ft_dump_verbose_flags(t_env *env)
{
	if (env->verbose_level == 0)
		ft_printf(" only essentials\n");
	else
	{
		ft_printf(":\n");
		if (env->verbose_level & VERBOSE_LIVES_FLAG)
			ft_printf("\t\t- show lives\n");
		if (env->verbose_level & VERBOSE_CYCLES_FLAG)
			ft_printf("\t\t- show cycles\n");
		if (env->verbose_level & VERBOSE_OPERATIONS_FLAG)
			ft_printf("\t\t- show operations (Params are NOT litteral ...)\n");
		if (env->verbose_level & VERBOSE_DEATH_FLAG)
			ft_printf("\t\t- show deaths\n");
		if (env->verbose_level & VERBOSE_PC_MOVEMENT_FLAG)
			ft_printf("\t\t- show PC movements (Except for jumps)\n");
	}
}

void		ft_dump_flags(t_env *env)
{
	if (env->flags & AFF_FLAG)
		ft_printf("\tPrint output from 'aff'\n");
	if (env->flags & DUMP_FLAG)
		ft_printf("\tDump memory after %zu cycles then exit\n", env->dump_cycles);
	if (env->flags & CYCLE_DUMP_FLAG)	
		ft_printf("\tDump memory every %zu cycles\n", env->cycle_dump_cycles);
	if (env->flags & VERBOSE_FLAG)
	{
		ft_printf("\tVerbose is activated with ");
		ft_dump_verbose_flags(env);
	}
}

void		ft_dump_header(t_header *header)
{
	ft_printf("\t\t\tmagic number : %#06x\n", header->magic);	
	ft_printf("\t\t\tname : %s\n", header->prog_name);
	ft_printf("\t\t\tprog size = %u\n", header->prog_size);
	ft_printf("\t\t\tcomment = %s\n", header->comment);
}

void		ft_dump_champs(t_env *env)
{
	t_champ	*ptr;

	ptr = env->champs;
	ft_printf("Contains champs :\n");
	while (ptr)
	{
		ft_printf("\tChampion in file %s\n", ptr->filename);
		ft_printf("\t\tWith fd : %d\n", ptr->fd);
		ft_printf("\t\twhich contains %S\n", ptr->content);
		ft_printf("\t\tWith header :\n");
		ft_dump_header(&(ptr->header));
		ptr = ptr->next;
	}
}

void		ft_dump_env(t_env *env)
{
	ft_printf("prog_name = %s\n", env->prog_name);
	ft_printf("with flags :\n");
	ft_dump_flags(env);
	ft_dump_champs(env);
}

unsigned int	ft_swap(unsigned int toswap)
{
	unsigned int	swapped;

	swapped = ((toswap>>24)&0xff) |
                    ((toswap<<8)&0xff0000) |
                    ((toswap>>8)&0xff00) |
                    ((toswap<<24)&0xff000000);
	return (swapped);
}

void		ft_wrong_magic(t_champ *champ)
{
	ft_dprintf(2, "%s : wrong magic number\n", champ->filename);
}


// tres peu de gestion d'erreur la dessous 
int			ft_parse_magic(t_champ *champ)
{
	int		retval;

	retval = read(champ->fd, &(champ->header.magic), 4);
	if (retval == -1)
	{
		ft_read_error(champ);
		return (0);
	}
	champ->header.magic = ft_swap(champ->header.magic);
	ft_offset_head(ft_get_env(), champ, 4);
	if (champ->header.magic != COREWAR_EXEC_MAGIC)
	{
		ft_wrong_magic(champ);
		return (0);
	}
	return (1);
}

int			ft_parse_name(t_champ *champ)
{
	int		retval;
	char	*name;

	retval = ft_parse_str(champ, &name);
	if (retval == 0) // gerer -1 aussi
	{
		ft_printf("failed\n");
		return (0);
	}
	if (ft_strlen(name) > PROG_NAME_LENGTH)
		ft_printf("name too big\n");
	ft_strcpy(champ->header.prog_name, name);
	ft_offset_head(ft_get_env(), champ, PROG_NAME_LENGTH + 1);
	return (1);
}

int			ft_parse_prog_size(t_champ *champ)
{
	int		retval;

	char	buf[300];

	read(champ->fd, buf, 299);
	buf[299] = 0;
	int i = 0;
	while (i < 299)
	{
		ft_putnbr(i);
		ft_putchar(buf[i]);
		ft_putchar('\n');
		i++;
	}
	ft_printf("\n");
	retval = read(champ->fd, &(champ->header.prog_size), 4);
	ft_offset_head(ft_get_env(), champ, 4);
	champ->header.prog_size = ft_swap(champ->header.prog_size);
	return (1);
}

int			ft_parse_comment(t_champ *champ)
{
	int		retval;
	char	*comment;

	retval = ft_parse_str(champ, &comment);
	if (retval == 0) // gerer -1 aussi
	{
		ft_printf("failed\n");
		return (0);
	}
	if (ft_strlen(comment) > COMMENT_LENGTH)
		ft_printf("comment too big\n");
	ft_strcpy(champ->header.comment, comment);
	ft_offset_head(ft_get_env(), champ, COMMENT_LENGTH);
	ft_printf("%s\n", comment);
	return (1);
}


int			ft_parse_champ(t_champ *champ)
{

	if (champ->fd == -1)
	{
		ft_open_error(champ);
		return (0);
	}
	read(champ->fd, &(champ->header), sizeof(t_header));
	champ->header.magic = ft_swap(champ->header.magic);
	champ->header.prog_size = ft_swap(champ->header.prog_size);
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

void		ft_parse_champs(t_env *env)
{
	t_champ	*ptr;
	t_champ	*tmp;

	ptr = env->champs;
	while (ptr)
	{
		if (!ft_parse_champ(ptr))
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
	if (!ft_parse_params(&env, ac - 1, av + 1))
		return (-1);
	ft_parse_champs(&env);
	ft_dump_env(&env);
	ft_free_env(&env);
	return (0);
}
