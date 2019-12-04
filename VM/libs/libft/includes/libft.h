/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 12:09:17 by toliver           #+#    #+#             */
/*   Updated: 2019/07/21 22:32:31 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <float.h>
# include <stdlib.h>
# include <sys/uio.h>
# include <sys/types.h>

# define BUFF_SIZE 512

typedef	struct		s_lst
{
	char			*str;
	int				fd;
	struct s_lst	*next;
}					t_lst;

char				**ft_split(char *str, char *charset);
int					ft_gnl(const int fd, char **line);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_strclr(char *s);
void				ft_strdel(char **as);
void				ft_striter(char *s, void (*f)(char*));
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				ft_bzero(void *b, size_t len);
void				*ft_memset(void *ptr, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t len);
void				*ft_memccpy(void *dst, const void *src, int c, size_t len);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *b, int c, size_t len);
char				*ft_strnew(size_t size);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s, const char *append);
char				*ft_strncat(char *s, const char *append, size_t count);
char				*ft_strdup(const char *str);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char*little);
char				*ft_strnstr(const char *big, const char*little, size_t len);
char				*ft_ftoa(float n, unsigned int decitoprint);
char				*ft_itoa(int n);
char				*ft_itoa_base(unsigned int value, unsigned int base);
char				*ft_itoa_hex(unsigned int value, int maj);
char				**ft_strsplit(char const *s, char c);
char				*ft_strtrim(char const *s);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					ft_get_next_line(const int fd, char **line);
int					ft_tolower(int c);
char				*ft_string_tolower(char *str);
int					ft_toupper(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_atoi(const char *str);
int					ft_atoi_base(const char *str, unsigned int from);
int					ft_memcmp(const void *b1, const void *b2, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strcmp_case_insensitive(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t len);
size_t				ft_strlen(const char *s);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);

#endif
