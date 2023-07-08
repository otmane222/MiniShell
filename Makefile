# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/17 14:33:03 by oaboulgh           #+#    #+#              #
#    Updated: 2023/06/11 14:00:29 by oaboulgh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =    minishell

CC = cc

SRCS = execution/execute.c \
	execution/and.c \
	execution/append.c \
	execution/cmd_utils.c \
	execution/cmd_utils2.c \
	execution/cmd_utils3.c \
	execution/command.c \
	execution/here_doc.c \
	execution/pipe.c \
	execution/red_in.c \
	execution/red_out.c \
	execution/shell_level.c \
	built_in_cmd/cd.c \
	built_in_cmd/echo.c \
	built_in_cmd/env.c \
	built_in_cmd/exit.c \
	built_in_cmd/export.c \
	built_in_cmd/pwd.c \
	built_in_cmd/unset.c \
	cedar/ast_and_or.c \
	cedar/ast_pipe.c \
	cedar/ast_redirection.c \
	cedar/red_utils.c \
	cedar/red_utils2.c \
	cedar/red_utils3.c \
	cedar/tree.c \
	envirenment/env.c \
	envirenment/env_utils.c \
	expander/expand.c \
	expander/expand_line2.c \
	expander/expand_line2_utils.c \
	expander/expand_utils.c \
	expander/expand_utils3.c \
	expander/expand_utils4.c \
	free/free.c \
	get_next_line/get_next_line_bonus.c \
	get_next_line/get_next_line_utils_bonus.c \
	lexer/2d_array_utils.c \
	lexer/bring_cmd_first.c \
	lexer/get_type.c \
	lexer/join_cmd.c \
	lexer/lexer.c \
	lexer/lexer_utils.c \
	parser/check_errors.c \
	parser/check_errors_utils.c \
	signals/signals.c \
	signals/signals_utils.c \
	wildcard/wild_card_char.c \
	wildcard/wild_card_utils6.c \
	wildcard/wildcard.c \
	wildcard/wildcard_utils.c \
	wildcard/wildcard_utils2.c \
	wildcard/wildcard_utils3.c \
	wildcard/wildcard_utils4.c \
	wildcard/wildcard_utils5.c \
	tokenizer/del_q.c \
	tokenizer/handle_chars.c \
	tokenizer/handle_dquotes.c \
	tokenizer/handle_parenthese.c \
	tokenizer/handle_separators.c \
	tokenizer/handle_spaces.c \
	tokenizer/handle_squotes.c \
	tokenizer/tokenizer.c \
	minishell.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror
LFLAGS = "-L$(shell brew --prefix readline)/lib"
IFLAGS = "-I$(shell brew --prefix readline)/include"

HEADERS = minishell.h \
		envirenment/env.h \
		tokenizer/tokenizer.h \
		expander/expand.h \
		lexer/lexer.h \
		execution/execute.h \
		parser/parser.h \
		built_in_cmd/builtin.h\
		get_next_line/get_next_line.h \
		$(shell brew --prefix readline)/include \
		wildcard/wildcard.h \
		libft/libft.h \
		ft_printf_error/ft_printf.h \
		free/free.h \
		cedar/tree.h \

HEADER_INC = -I$(shell brew --prefix readline)/include


RM = rm -rf

LIBS = libft/libft.a \
		ft_printf_error/libftprintf.a

all: $(NAME)
	@printf " \033[1;32m                          MINISHELL is built successfully!\033               \033[1;38m 		       \033[0m         \033[0m\n"

$(NAME): libft_rule printf_rule $(OBJS) $(LIBS)
	@$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $@ -lreadline $(LFLAGS)

printf_rule:
	@make -C ft_printf_error

libft_rule:
	@make bonus -C libft

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