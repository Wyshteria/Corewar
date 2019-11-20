/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:30:16 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 19:40:55 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <sys/types.h>
# include <wchar.h>
# include <stddef.h>

# define BUFFSIZE 2048
# define DBL_MAX_EXP_VAL 0x7FF
# define LDBL_MAX_EXP_VAL 0x7FFF
# define ISHEXA 3
# define ISSHORTEST 2
# define ISEXP 1
# define ISDECI 0

typedef union				u_types
{
	int						i;
	signed char				sc;
	short int				si;
	long int				li;
	long long int			lli;
	intmax_t				imax;
	size_t					siz;
	ptrdiff_t				ptd;
	unsigned int			ui;
	unsigned char			uc;
	unsigned short int		usi;
	unsigned long int		uli;
	unsigned long long int	ulli;
	uintmax_t				uimax;
	double					d;
	long double				ld;
	wint_t					wi;
	char					*cptr;
	wchar_t					*wcptr;
	int						*iptr;
	void					*vptr;
	signed char				*scptr;
	short int				*siptr;
	long int				*liptr;
	long long int			*lliptr;
	intmax_t				*imaxptr;
	size_t					*sizptr;
	ptrdiff_t				*ptdptr;
}							t_types;

typedef struct				s_arg
{
	int						param;
	char					flags;
	int						width;
	int						prec;
	int						length;
	int						type;
	int						cat;
	t_types					argument;
}							t_arg;

typedef struct				s_penv
{
	const char				*str;
	const char				*strcopy;
	char					buff[BUFFSIZE];
	int						printflen;
	char					*printfstr;
	int						is_whatprintf;
	int						fd;
	int						buffilasttoken;
	int						buffi;
	int						lastparam;
	va_list					arg;
	int						(*parse[255])(struct s_penv*, t_arg*);
	int						(*get_arg[5][10])(struct s_penv*, t_arg*);
	char					null[7];
}							t_penv;
/*
**	FLOAT HANDLING STRUCTURES
*/
typedef struct				s_ldoublesplit
{
	unsigned long int		fra:63;
	unsigned int			intpart:1;
	unsigned int			exp:15;
	unsigned int			sign:1;
}							t_ldoublesplit;
typedef union				u_ldouble
{
	long double				val;
	t_ldoublesplit			value;
}							t_ldouble;
typedef	struct				s_doublesplit
{
	unsigned long long int	fra:52;
	unsigned int			exp:11;
	unsigned int			sign:1;
}							t_doublesplit;
typedef	union				u_double
{
	double					val;
	t_doublesplit			value;
}							t_double;
/*
**	HEXA STRUCT
*/
typedef union				u_hexa
{
	unsigned long long int	fra;
	unsigned char			byte[8];
}							t_hexa;
typedef struct				s_splitd
{
	unsigned int			sign:1;
	int						exp;
	unsigned long int		fra:64;
	int						prec;
	int						width;
	int						intsize;
	int						decisize;
	int						isrounded:1;
	unsigned int			isnan:1;
	unsigned int			isinf:1;
	unsigned int			iszero:1;
	unsigned int			islong:1;
	unsigned int			issub:1;
	unsigned int			isuppercase:1;
	unsigned int			type:2;
}							t_splitd;
typedef struct				s_bigint
{
	long long unsigned int	number[968];
	long long unsigned int	value[968];
	char					fullnum[16457];
	int						fullnumbuffer;
	int						comapos;
	int						rank;
	int						exp;
}							t_bigint;
/*
** add __attribute__((format(printf,1,2))); to have compilation error like real
*/
int							ft_printf(const char *str, ...);
char						*ft_sprintf(const char *str, ...);
int							ft_dprintf(int fd, const char *str, ...);
/*
** BUFFER FILLING FUNCTIONS
*/
int							parse_string(t_penv *env);
int							parse_token(t_penv *env);
int							parse_minusflag(t_penv *env, t_arg *arg);
int							parse_plusflag(t_penv *env, t_arg *arg);
int							parse_zeroflag(t_penv *env, t_arg *arg);
int							parse_spaceflag(t_penv *env, t_arg *arg);
int							parse_hashflag(t_penv *env, t_arg *arg);
int							parse_apostropheflag(t_penv *env, t_arg *arg);
int							parse_wildchar(t_penv *env, t_arg *arg);
int							parse_number(t_penv *env, t_arg *arg);
int							parse_error(t_penv *env, t_arg *arg);
int							parse_preci(t_penv *env, t_arg *arg);
int							parse_jconv(t_penv *env, t_arg *arg);
int							parse_zconv(t_penv *env, t_arg *arg);
int							parse_lmajconv(t_penv *env, t_arg *arg);
int							parse_tconv(t_penv *env, t_arg *arg);
int							parse_lconv(t_penv *env, t_arg *arg);
int							parse_hconv(t_penv *env, t_arg *arg);
int							get_int(t_penv *env, t_arg *arg);
int							get_char(t_penv *env, t_arg *arg);
int							get_short(t_penv *env, t_arg *arg);
int							get_long(t_penv *env, t_arg *arg);
int							get_longlong(t_penv *env, t_arg *arg);
int							get_intmaxt(t_penv *env, t_arg *arg);
int							get_sizet(t_penv *env, t_arg *arg);
int							get_ptrdifft(t_penv *env, t_arg *arg);
int							get_ldouble(t_penv *env, t_arg *arg);
int							get_double(t_penv *env, t_arg *arg);
int							get_int(t_penv *env, t_arg *arg);
int							get_wintt(t_penv *env, t_arg *arg);
int							get_ptr(t_penv *env, t_arg *arg);
intmax_t					get_castedintmaxt(t_arg *arg);
intmax_t					get_casteduintmaxt(t_arg *arg);
int							parse_pcsize(t_penv *env, t_arg *arg);
int							parse_dsize(t_penv *env, t_arg *arg);
int							parse_bigdsize(t_penv *env, t_arg *arg);
int							parse_osize(t_penv *env, t_arg *arg);
int							parse_bigosize(t_penv *env, t_arg *arg);
int							parse_usize(t_penv *env, t_arg *arg);
int							parse_bigusize(t_penv *env, t_arg *arg);
int							parse_xsize(t_penv *env, t_arg *arg);
int							parse_bigxsize(t_penv *env, t_arg *arg);
int							parse_csize(t_penv *env, t_arg *arg);
int							parse_bigcsize(t_penv *env, t_arg *arg);
int							parse_ssize(t_penv *env, t_arg *arg);
int							parse_bigssize(t_penv *env, t_arg *arg);
int							parse_nsize(t_penv *env, t_arg *arg);
int							parse_psize(t_penv *env, t_arg *arg);
int							parse_esize(t_penv *env, t_arg *arg);
int							parse_fsize(t_penv *env, t_arg *arg);
int							parse_gsize(t_penv *env, t_arg *arg);
int							parse_asize(t_penv *env, t_arg *arg);
void						flags_cleanup(t_arg *arg);
void						fill_buffer(t_penv *env, char c, int i);
int							get_arg(t_penv *env, t_arg *arg);
void						arg_parse(t_penv *env, t_arg *arg);
int							buff_fillc(t_penv *env, t_arg *arg);
int							buff_fillwchar(t_penv *env, t_arg *arg);
int							buff_putwchar(t_penv *env, wint_t unicode);
int							buff_fills(t_penv *env, t_arg *arg);
int							buff_fillwstr(t_penv *env, t_arg *arg);
int							buff_fillint(t_penv *env, t_arg *arg);
int							buff_filloct(t_penv *env, t_arg *arg);
int							buff_fillhexa(t_penv *env, t_arg *arg);
int							buff_filluint(t_penv *env, t_arg *arg);
int							buff_fillchar(t_penv *env, t_arg *arg);
int							buff_fillptr(t_penv *env, t_arg *arg);
int							buff_fillnptr(t_penv *env, t_arg *arg);
int							buff_putprefix(t_penv *env, char c, int ishash);
/*
** FONCTIONS A L'ESSAI
*/
int							buff_fillbinary(t_penv *env, t_arg *arg);
int							parse_bsize(t_penv *env, t_arg *arg);
int							buff_fillfloat(t_penv *env, t_arg *arg);
int							buff_fillexplong(t_splitd *num, t_penv *env,
										t_arg *arg);
int							buff_fillexp(t_splitd *num, t_bigint *number,
										t_penv *env, t_arg *arg);
int							buff_fillfloatdeci(t_splitd *num, t_bigint *number,
										t_penv *env, t_arg *arg);
int							fill_bigint(t_bigint *number, t_splitd *num);
int							float_rounding(t_bigint *number, int *prec);
int							putfloatsign(int sign, char flags, t_penv *env);
int							mulnum(t_bigint *num, int value);
int							multab(t_bigint *num, int value);
int							divtab(t_bigint *num, int value);
int							addtab(t_bigint *num);
int							buff_uimaxtoahexa(t_penv *env, uintmax_t value);
int							buff_uimaxtoaoct(t_penv *env, uintmax_t value);
int							float_writeexpoutput(t_bigint *number,
										t_splitd *num, t_penv *env, t_arg *arg);
int							sizeofexponent(int exp);
int							putexponent (int exp, int isuppercase, t_penv *env);
int							float_writeoutput(t_bigint *number, t_splitd *num,
									t_penv *env, t_arg *arg);
int							fill_bigint(t_bigint *number, t_splitd *num);
int							copydecivalue(t_bigint *number);
int							write_bigint(t_bigint *number);
int							filldeci(t_bigint *number, t_splitd *num);
size_t						ft_wstrlen(wint_t *str);
size_t						ft_pstrlen(char *str);
size_t						chartofill(t_arg *arg, int wchar);
size_t						ft_wcharstrlen(t_penv *env, t_arg *arg);
int							issmaller(wchar_t *str, int prec);
intmax_t					get_castedintmaxt(t_arg *arg);
intmax_t					get_casteduintmaxt(t_arg *arg);
int							hexavaluesetd(t_hexa hex, t_splitd *num,
									char value[]);
int							roundinghexa(t_splitd *num, char value[]);
int							setaswritable(char value[], int size, int uppercas);
int							writehexa(t_splitd *num, t_penv *env, char value[],
									t_arg *arg);
int							splitinit(t_arg *arg, t_splitd *num, t_penv *env);
int							buff_fillerror(t_splitd *num, t_penv *env,
									t_arg *arg);
int							numberlen(int number);
int							buff_fillexponenthexa(t_penv *env, int up, int exp);
/*
** BUFFER HANDLING FUNCTIONS
*/
void						buff_flush(t_penv *env);
void						buff_check(t_penv *env);
int							buff_padding(t_penv *env, t_arg *arg, int width);
int							buff_fillwith(t_penv *env, char c);
int							buff_fillwithstr(t_penv *env, char *str);
int							buff_fillwithnumber(t_penv *env, char c, int i);
int							buff_fillnumber(t_penv *env, int nbr);
int							buff_padding(t_penv *env, t_arg *arg, int width);
int							buff_uimaxtoahexa(t_penv *env, uintmax_t value);
/*
** UTILITY
*/
void						arg_init(t_arg *arg);
void						env_pinit(t_penv *env, const char *str);
void						env_ptrarrayinit(t_penv *env);
void						env_getarrayinit(t_penv *env);
int							pfatoi(t_penv *env);
intmax_t					get_castedintmaxt(t_arg *arg);
size_t						ft_intmaxtlenbase(intmax_t value, int base);
size_t						ft_uintmaxtlenbase(uintmax_t value, int base);
int							octsize(wchar_t nbr);
int							buff_imaxtoa(t_penv *env, intmax_t value);
int							buff_uimaxtoa(t_penv *env, uintmax_t value);
#endif
