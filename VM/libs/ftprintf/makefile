# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/12 01:24:53 by toliver           #+#    #+#              #
#    Updated: 2019/01/07 16:27:39 by toliver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Werror -Wextra -Wall -Ofast

FILES = ft_printf \
		parsing \
		bufferhandling \
		buff_fill1 \
		parse_flag1 \
		parse_flag2 \
		parse_conv1 \
		parse_conv2 \
		parse_size \
		parse_size1 \
		parse_size2 \
		parse_size3 \
		parse_size4 \
		parse_size5 \
		get_arg1 \
		get_arg2 \
		get_arg3 \
		buff_fillfloat \
		buff_fillbinary \
		buff_fillutility \
		buff_fillchar \
		buff_fillhexaoct \
		buff_fillfloat \
		buff_fillfloat_exp \
		buff_fillfloat_deci \
		bigint_handle \
		buff_fillhexaoctutil \
		buff_fillfloat_exp_write \
		buff_fillfloat_deci_write \
		fillfloat_deci_bigint \
		fillfloat_deci_bigint2 \
		buff_fill_utility \
		buff_fillint_getcasted \
		buff_fillptr \
		buff_fillint \
		buff_fillint_utility \
		parsing1 \
		env_ptrarrayinit \
		buff_fillfloatinit \
		buff_fillfloat_roundinghexa \
		buff_fillfloat_writehexa \
		buff_fillfloat_error \
		buff_fillfloat_hexautil  

SRC = $(addsuffix .c, $(FILES))

SRC_PATH = ./srcs/

SRCS = $(addprefix $(SRC_PATH),$(SRC))

OBJ_PATH = ./objs/

OBJS = $(addprefix $(OBJ_PATH),$(SRC:.c=.o))

INCLUDES = -I./includes/

HEADERS = includes/libftprintf.h \

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): objs $(OBJS) $(HEADERS)
	@printf  "\033[92m\033[1:32mCompiling -------------> \033[91m$(NAME)\033[0m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@ar rcs $(NAME) $(OBJS)

objs/%.o: srcs/%.c $(HEADERS)
	@printf  "\033[1:92mCompiling $(NAME)\033[0m %-31s\033[32m[$<]\033[0m\n" ""
	@gcc -o $@ -c $< $(FLAGS) $(INCLUDES)
	@printf "\033[A\033[2K"

objs:
	@mkdir objs/

clean:
	@rm -rf ./objs
	@printf  "\033[1:32mCleaning object files -> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"

fclean: clean
	@rm -rf $(NAME)
	@printf  "\033[1:32mCleaning binary -------> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"

re: fclean all
