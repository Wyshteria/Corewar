/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ptrarrayinit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:59:32 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:34:17 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void							env_getarrayinittab(t_penv *env)
{
	env->get_arg[0][0] = &get_int;
	env->get_arg[0][1] = &get_char;
	env->get_arg[0][2] = &get_short;
	env->get_arg[0][3] = &get_long;
	env->get_arg[0][4] = &get_longlong;
	env->get_arg[0][5] = &get_intmaxt;
	env->get_arg[0][6] = &get_sizet;
	env->get_arg[0][7] = &get_ptrdifft;
	env->get_arg[1][8] = &get_ldouble;
	env->get_arg[1][0] = &get_double;
	env->get_arg[2][0] = &get_int;
	env->get_arg[2][3] = &get_wintt;
	env->get_arg[3][0] = &get_ptr;
	env->get_arg[4][0] = &get_int;
	env->get_arg[4][1] = &get_char;
	env->get_arg[4][2] = &get_short;
	env->get_arg[4][3] = &get_long;
	env->get_arg[4][4] = &get_longlong;
	env->get_arg[4][5] = &get_intmaxt;
	env->get_arg[4][6] = &get_sizet;
	env->get_arg[4][7] = &get_ptrdifft;
	env->get_arg[4][8] = &get_double;
	env->get_arg[4][9] = &get_ldouble;
}

void							env_getarrayinit(t_penv *env)
{
	int							i;
	int							j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 10)
			env->get_arg[i][j] = NULL;
	}
	env_getarrayinittab(env);
}

void							env_ptrarrayinit0(t_penv *env)
{
	env->parse[106] = &parse_jconv;
	env->parse[122] = &parse_zconv;
	env->parse[76] = &parse_lmajconv;
	env->parse[116] = &parse_tconv;
	env->parse[108] = &parse_lconv;
	env->parse[104] = &parse_hconv;
	env->parse[37] = &parse_pcsize;
	env->parse[100] = &parse_dsize;
	env->parse[68] = &parse_bigdsize;
	env->parse[105] = &parse_dsize;
	env->parse[111] = &parse_osize;
	env->parse[79] = &parse_bigosize;
	env->parse[117] = &parse_usize;
	env->parse[85] = &parse_bigusize;
	env->parse[120] = &parse_xsize;
	env->parse[88] = &parse_bigxsize;
	env->parse[99] = &parse_csize;
	env->parse[67] = &parse_bigcsize;
	env->parse[115] = &parse_ssize;
	env->parse[83] = &parse_bigssize;
	env->parse[110] = &parse_nsize;
	env->parse[112] = &parse_psize;
}

void							env_ptrarrayinit1(t_penv *env)
{
	env->parse[101] = &parse_esize;
	env->parse[69] = &parse_esize;
	env->parse[102] = &parse_fsize;
	env->parse[70] = &parse_fsize;
	env->parse[103] = &parse_gsize;
	env->parse[71] = &parse_gsize;
	env->parse[97] = &parse_asize;
	env->parse[65] = &parse_asize;
	env->parse[98] = &parse_bsize;
	env->parse[66] = &parse_bsize;
}

void							env_ptrarrayinit(t_penv *env)
{
	int							i;

	i = -1;
	while (++i < 128)
		env->parse[i] = &parse_error;
	env->parse[48] = &parse_zeroflag;
	env->parse[43] = &parse_plusflag;
	env->parse[45] = &parse_minusflag;
	env->parse[32] = &parse_spaceflag;
	env->parse[35] = &parse_hashflag;
	env->parse[39] = &parse_apostropheflag;
	env->parse[46] = &parse_preci;
	env->parse[42] = &parse_wildchar;
	i = 49;
	while (i >= 49 && i <= 57)
	{
		env->parse[i] = &parse_number;
		i++;
	}
	env_ptrarrayinit0(env);
	env_ptrarrayinit1(env);
}
