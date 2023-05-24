# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nakebli <nakebli@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/17 14:33:03 by nakebli           #+#    #+#              #
#    Updated: 2023/05/22 14:29:15 by nakebli          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =    minishell

SRCS =	$(wildcard envirenment/*.c) \
		$(wildcard tokenizer/*.c) \
		$(wildcard expander/*.c) \
		$(wildcard lexer/*.c) \
		$(wildcard parser/*.c) \
		$(wildcard cedar/*.c) \
		$(wildcard execution/*.c) \
		$(wildcard built_in_cmd/*.c) \
		$(wildcard get_next_line/*.c) \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

HEADER = minishell.h \
	envirenment/env.h \
	tokenizer/tokenizer.h \
	expander/expand.h \
	execution/execute.h \
	parser/parser.h \
	built_in_cmd/builtin.h\
	get_next_line/get_next_line.h \

RM = rm -rf

all: $(NAME) $(OBJS) $(HEADER)
	@printf " \033[1;38m   ▄▄▄▄███▄▄▄▄    ▄█  ███▄▄▄▄    ▄█     ▄████████    ▄█    █▄       ▄████████  ▄█        ▄█       \033[0m\n"
	@printf " \033[1;37m ▄██▀▀▀███▀▀▀██▄ ███  ███▀▀▀██▄ ███    ███    ███   ███    ███     ███    ███ ███       ███       \033[0m\n"
	@printf " \033[1;38m ███   ███   ███ ███▌ ███   ███ ███▌   ███    █▀    ███    ███     ███    █▀  ███       ███       \033[0m\n"
	@printf " \033[1;37m ███   ███   ███ ███▌ ███   ███ ███▌   ███         ▄███▄▄▄▄███▄▄  ▄███▄▄▄     ███       ███       \033[0m\n"
	@printf " \033[1;38m ███   ███   ███ ███▌ ███   ███ ███▌ ▀███████████ ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀     ███       ███       \033[0m\n"
	@printf " \033[1;37m ███   ███   ███ ███  ███   ███ ███           ███   ███    ███     ███    █▄  ███       ███       \033[0m\n"
	@printf " \033[1;38m ███   ███   ███ ███  ███   ███ ███     ▄█    ███   ███    ███     ███    ███ ███▌    ▄ ███▌    ▄ \033[0m\n"
	@printf " \033[1;37m  ▀█   ███   █▀  █▀    ▀█   █▀  █▀    ▄████████▀    ███    █▀      ██████████ █████▄▄██ █████▄▄██ \033[0m\n"
	@printf " \033[1;32m                          MINISHELL is built successfully!\033               \033[1;38m 		       \033[0m         \033[0m\n"

%.o: %.c $(HEADER) libft/libft.h
	@gcc -c $(CFLAGS) $<  -o $@ 
	@printf "\033[0;32m[compiling : %-30s .....] \033[0;0m \r" ${notdir $@}

$(NAME): $(OBJS) minishell.o $(HEADER)
	make bonus -C libft
	@gcc  minishell.c -I/path/to/readline/include -lreadline -o $(NAME) $(OBJS) libft/libft.a

clean:
	$(RM) $(OBJS) minishell.o
	make clean -C libft
	@printf "\033[0;32mCLEANED 🗑️\033[0;0m\n"

fclean:clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.SILENT : $(NAME) clean fclean re

.PHONY : all clean fclean re