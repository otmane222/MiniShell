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

CC = cc

SRCS =	$(wildcard envirenment/*.c) \
		$(wildcard tokenizer/*.c) \
		$(wildcard expander/*.c) \
		$(wildcard wildcard/*.c) \
		$(wildcard lexer/*.c) \
		$(wildcard parser/*.c) \
		$(wildcard cedar/*.c) \
		$(wildcard execution/*.c) \
		$(wildcard built_in_cmd/*.c) \
		$(wildcard get_next_line/*.c) \
		minishell.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
LFLAGS = -L/Users/nakebli/.brew/opt/readline/lib 
IFLAGS = -I/Users/nakebli/.brew/opt/readline/include

HEADERS = minishell.h \
		envirenment/env.h \
		tokenizer/tokenizer.h \
		expander/expand.h \
		execution/execute.h \
		parser/parser.h \
		built_in_cmd/builtin.h\
		get_next_line/get_next_line.h \
		/Users/nakebli/.brew/opt/readline/include \
		libft/libft.h \
		ft_printf_error/ft_printf.h

HEADER_INC =	-Iminishell.h \
				-Ienvirenment/env.h \
				-Itokenizer/tokenizer.h \
				-Iexpander/expand.h \
				-Iexecution/execute.h \
				-Iparser/parser.h \
				-Ibuilt_in_cmd/builtin.h\
				-Iget_next_line/get_next_line.h \
				-I/Users/nakebli/.brew/opt/readline/include


RM = rm -rf

LIBS = libft/libft.a \
		ft_printf_error/libftprintf.a

all: $(NAME)
	@printf " \033[1;32m                          MINISHELL is built successfully!\033               \033[1;38m 		       \033[0m         \033[0m\n"

$(NAME): $(OBJS)
	make bonus -C libft
	make -C ft_printf_error
	@$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $@ -lreadline $(LFLAGS)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADER_INC)
	@printf "\033[0;32m[compiling : %-30s .....] \033[0;0m \r" ${notdir $@}

clean:
	$(RM) $(OBJS)
	make clean -C libft
	make clean -C ft_printf_error
	@printf "\033[0;32mCLEANED 🗑️\033[0;0m\n"

fclean:clean
	$(RM) $(NAME)
	make fclean -C libft
	make fclean -C ft_printf_error

re: fclean all

.SILENT : $(NAME) clean fclean re

.PHONY : all clean fclean re