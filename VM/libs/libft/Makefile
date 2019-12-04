# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/12 01:24:53 by toliver           #+#    #+#              #
#    Updated: 2019/08/10 21:32:00 by toliver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror -Ofast

FILES = atoi \
		atoll \
		bzero \
		isalnum \
		isalpha \
		isascii \
		isdigit \
		isprint \
		itoa \
		memalloc \
		memccpy \
		memchr \
		memcmp \
		memcpy \
		memdel \
		memmove \
		memset \
		putchar \
		putchar_fd \
		putendl \
		putendl_fd \
		putstr \
		putstr_fd \
		putnbr \
		putnbr_fd \
		strcat \
		strchr \
		strclr \
		strcmp \
		strcpy \
		strdel \
		strdup \
		strequ \
		striter \
		striteri \
		strjoin \
		strlcat \
		strlen \
		strmap \
		strmapi \
		strncat \
		strncmp \
		strncpy \
		strnequ \
		strnew \
		strnstr \
		strrchr \
		strsplit \
		strstr \
		strsub \
		strtrim \
		split \
		tolower \
		toupper \
		get_next_line \
		gnl \

INCLUDES = -I./includes

OBJS = $(addprefix objs/, $(addsuffix .o, \
	   $(addprefix ft_, $(FILES)) \
	   ))

.PHONY: all clean fclean re

all: $(NAME)

analyze: 
	gcc --analyze $(addprefix srcs/, $(addsuffix .c, $(addprefix ft_, $(FILES))))  $(INCLUDES)
	#	gcc -fsyntax-only $(addprefix srcs/, $(addsuffix .c, $(addprefix ft_, $(FILES))))  $(INCLUDES)

$(NAME): objs $(OBJS)
	@printf  "\033[92m\033[1:32mCompiling -------------> \033[91m$(NAME)\033[0m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@ar rcs $(NAME) $(OBJS)

objs/%.o: srcs/%.c
	@printf  "\033[1:92mCompiling $(NAME)\033[0m %-31s\033[32m[$<]\033[0m\n" ""
	@gcc -o $@ -c $< $(FLAGS) $(INCLUDES)
	@printf "\033[A\033[2K"

objs:
	mkdir -p objs/

clean:
	@rm -rf $(OBJS)
	@printf  "\033[1:32mCleaning object files -> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"

fclean: clean
	@rm -rf $(NAME)
	@printf  "\033[1:32mCleaning binary -------> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"

re: fclean all
