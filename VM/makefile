# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/20 19:50:33 by toliver           #+#    #+#              #
#    Updated: 2019/12/07 22:45:49 by toliver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = vm

INCLUDES = -I includes\
		   -I ./libs/libft/includes\
		   -I ./libs/ftprintf/includes

LIBS =	./libs/libft/libft.a\
		./libs/ftprintf/libftprintf.a\

FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

OBJS = $(addprefix objs/, $(addsuffix .o, \
			$(addprefix vm/, \
				main \
				op\
				print \
				utils \
				env \
				params \
				free \
				champs \
				) \
		)) 

HEADERS = ./includes/vm.h ./includes/op.h

all: $(NAME)

$(NAME): $(LIBS) objs $(OBJS) $(HEADERS)
	@printf "\033[92m\033[1:32mCompiling -------------> \033[91m$(NAME)\033[0m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@gcc $(FLAGS) $(OBJS) $(INCLUDES) -o $(NAME) -lncurses $(LIBS) 

objs/%.o: srcs/%.c
	@printf  "\033[1:92mCompiling $(NAME)\033[0m %-31s\033[32m[$<]\033[0m\n" ""
	@gcc -o $@ -c $< $(FLAGS) -fPIC $(INCLUDES)
	@printf "\033[A\033[2K"

objs:
	@mkdir -p objs/vm

$(LIBS):
	@make -C ./libs/libft/.
	@make -C ./libs/ftprintf/.

clean:
	@printf  "\033[1:32mCleaning object files -> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@rm -rf objs

fclean: clean
	@printf  "\033[1:32mCleaning binary -------> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@rm -f $(NAME)
re:
	@$(MAKE) fclean
	@$(MAKE)
