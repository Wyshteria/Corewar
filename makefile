# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/20 19:50:33 by toliver           #+#    #+#              #
#    Updated: 2019/12/07 20:36:28 by toliver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_VM = corewar
NAME_ZAZ = corewar_zaz
NAME_ASM = asm

INCLUDES_ASM = -I includes\
		   -I ./libs/libft/includes\
		   -I ./libs/ftprintf/includes

INCLUDES_VM = -I includes\
		   -I ./libs/libft/includes\
		   -I ./libs/ftprintf/includes \
		   -I ~/.brew/include

LIBS =	./libs/libft/libft.a\
		./libs/ftprintf/libftprintf.a\

FLAGS = -Wall -Wextra -Werror -g3

OBJS_ASM = $(addprefix objs/, $(addsuffix .o, \
			$(addprefix asm/, \
				main \
				env \
				error \
				asm_error \
				files \
				parse_args \
				utils \
				parse_utils \
				print \
				print2 \
				token \
				ft_write_file \
				op \
				ft_operations \
				ft_params \
				ft_label \
				ft_check_header \
				ft_parse_op_utils \
				ft_program \
				) \
		)) 

OBJS_ZAZ = $(addprefix objs/, $(addsuffix .o, \
			$(addprefix vm/, \
				main \
				op\
				op1\
				op2\
				op3\
				op_zaz \
				print \
				print1 \
				utils \
				utils1 \
				utils2 \
				env \
				params \
				params1 \
				params2 \
				params3 \
				params4 \
				params5 \
				free \
				champs \
				champs1 \
				visu \
				visu1 \
				visu2 \
				visu3 \
				visu4 \
				visu5 \
				visu6 \
				arena \
				arena1 \
				verbose \
				verbose1 \
				running \
				running1 \
				running2 \
				running3 \
				) \
		)) 

OBJS_VM = $(addprefix objs/, $(addsuffix .o, \
			$(addprefix vm/, \
				main \
				op\
				op1\
				op2\
				op3\
				op_correc \
				print \
				print1 \
				utils \
				utils1 \
				utils2 \
				env \
				params \
				params1 \
				params2 \
				params3 \
				params4 \
				params5 \
				free \
				champs \
				champs1 \
				visu \
				visu1 \
				visu2 \
				visu3 \
				visu4 \
				visu5 \
				visu6 \
				arena \
				arena1 \
				verbose \
				verbose1 \
				running \
				running1 \
				running2 \
				running3 \
				) \
		)) 

HEADERS_ASM = ./includes/asm.h ./includes/op.h
HEADERS_VM = ./includes/vm.h ./includes/op.h ./includes/display.h

.PHONY: all
all: $(NAME_ASM) $(NAME_VM)

.PHONY: zaz
zaz: $(NAME_ZAZ)

.PHONY: test
test: test.c
	gcc -Wall -Werror -Wextra -I./includes test.c -o test

$(NAME_ASM): $(LIBS) objs/asm $(OBJS_ASM) $(HEADERS_ASM)
	@printf "\033[92m\033[1:32mCompiling -------------> \033[91m$(NAME_ASM)\033[0m:		\033[0m%-16s\033[32m[✔]\033[0m\n"
	@gcc $(FLAGS) $(OBJS_ASM) $(INCLUDES_ASM) -o $(NAME_ASM) $(LIBS) 

$(NAME_VM): $(LIBS) objs/vm $(OBJS_VM) $(HEADERS_VM)
	@printf "\033[92m\033[1:32mCompiling -------------> \033[91m$(NAME_VM)\033[0m:	\033[0m%-16s\033[32m[✔]\033[0m\n"
	@gcc `sdl2-config --cflags --libs` -lSDL2_ttf $(FLAGS) $(OBJS_VM) $(INCLUDES_VM) $(LIBS) -o $(NAME_VM) 

$(NAME_ZAZ): $(LIBS) objs/vm $(OBJS_ZAZ) $(HEADERS_VM)
	@printf "\033[92m\033[1:32mCompiling -------------> \033[91m$(NAME_ZAZ)\033[0m:	\033[0m%-16s\033[32m[✔]\033[0m\n"
	@gcc $(FLAGS) $(OBJS_ZAZ) $(INCLUDES_VM) -o $(NAME_ZAZ) `sdl2-config --cflags --libs` -lSDL2_ttf $(LIBS)

print:
	echo $(OBJS_VM)

objs/asm/%.o: srcs/asm/%.c
	@printf  "\033[1:92mCompiling $(NAME_ASM)		\033[0m %-31s\033[32m[$<]\033[0m\n" ""
	@gcc -o $@ -c $< $(FLAGS) -fPIC $(INCLUDES_ASM)
	@printf "\033[A\033[2K"

objs/vm/%.o: srcs/vm/%.c
	@printf  "\033[1:92mCompiling $(NAME_VM)	\033[0m %-31s\033[32m[$<]\033[0m\n" ""
	@gcc -o $@ -c $< $(FLAGS) -fPIC $(INCLUDES_VM)
	@printf "\033[A\033[2K"

objs/asm:
	@mkdir -p objs/asm

objs/vm:
	@mkdir -p objs/vm

$(LIBS):
	@make -C ./libs/libft/.
	@make -C ./libs/ftprintf/.

.PHONY: clean_zaz
clean_zaz:
	@printf  "\033[1:32mCleaning object files -> \033[91m$(NAME_ZAZ)\033[0m\033[1:32m:	\033[0m%-16s\033[32m[✔]\033[0m\n"
	@rm -f $(OBJS_ZAZ)

.PHONY: fclean_zaz
fclean_zaz: clean_zaz
	@printf  "\033[1:32mCleaning binary -------> \033[91m$(NAME_ZAZ)\033[0m\033[1:32m:	\033[0m%-16s\033[32m[✔]\033[0m\n"
	@rm -f $(NAME_ZAZ)

.PHONY: clean_vm clean_corewar
clean_corewar clean_vm:
	@printf  "\033[1:32mCleaning object files -> \033[91m$(NAME_VM)\033[0m\033[1:32m:	\033[0m%-16s\033[32m[✔]\033[0m\n"
	@rm -rf objs/vm

.PHONY: fclean_vm fclean_corewar
fclean_corewar fclean_vm: clean_vm
	@printf  "\033[1:32mCleaning binary -------> \033[91m$(NAME_VM)\033[0m\033[1:32m:	\033[0m%-16s\033[32m[✔]\033[0m\n"
	@rm -f $(NAME_VM)

.PHONY: clean_asm
clean_asm:
	@printf  "\033[1:32mCleaning object files -> \033[91m$(NAME_ASM)\033[0m\033[1:32m:		\033[0m%-16s\033[32m[✔]\033[0m\n"
	@rm -rf objs/asm

.PHONY: fclean_asm
fclean_asm: clean_asm
	@printf  "\033[1:32mCleaning binary -------> \033[91m$(NAME_ASM)\033[0m\033[1:32m:		\033[0m%-16s\033[32m[✔]\033[0m\n"
	@rm -f $(NAME_ASM)

.PHONY: clean
clean: clean_asm clean_vm
	@rm -rf objs

.PHONY: fclean
fclean: clean

.PHONY: re
re:
	@$(MAKE) fclean
	@$(MAKE)
