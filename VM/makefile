# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/20 19:50:33 by toliver           #+#    #+#              #
#    Updated: 2020/01/03 22:02:34 by toliver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = corewar

INCLUDES = -I includes\
		   -I ./libs/libft/includes\
		   -I ./libs/ftprintf/includes \
		   -I ~/.brew/include

LIBS =	./libs/libft/libft.a\
		./libs/ftprintf/libftprintf.a\

FLAGS = -Wall -Wextra -Werror -g3

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
				visu \
				arena \
				verbose \
				) \
		)) 

HEADERS = ./includes/vm.h ./includes/op.h ./includes/display.h

all: $(NAME)

$(NAME): $(LIBS) objs $(OBJS) $(HEADERS)
	@printf "\033[92m\033[1:32mCompiling -------------> \033[91m$(NAME)\033[0m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@gcc $(FLAGS) $(OBJS) $(INCLUDES) -o $(NAME) `sdl2-config --cflags --libs` -lSDL2_ttf $(LIBS) 

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
