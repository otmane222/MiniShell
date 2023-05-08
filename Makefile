# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 16:32:50 by oaboulgh          #+#    #+#              #
#    Updated: 2023/04/12 14:27:18 by oaboulgh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =    minishell

SRCS = minishell_utils.c \
	tokenizer/tokenizer.c \
	tokenizer/handle_dquotes.c \
	tokenizer/handle_squotes.c \
	tokenizer/handle_spaces.c \
	tokenizer/handle_chars.c \
	tokenizer/handle_separators.c \
	tokenizer/handle_parenthese.c \
	lexer/lexer.c \
	lexer/expand.c \
	lexer/lexer_utils.c \
	lexer/lexer_utils2.c \
	tree/tree.c \
	execution/execute.c \
	get_next_line_bonus.c \
	get_next_line_utils_bonus.c \
	built_in_cmd/pwd.c \

OBJS = $(SRCS:.c=.o)

CFLAGS =  # -Wall -Wextra -Werror

HEADER = minishell.h \
	tokenizer/tokenizer.h \
	lexer/lexer.h

RM = rm -rf

all: $(NAME) $(OBJS) $(HEADER)
	@printf "\033[0;32mDONE ✅"

%.o: %.c $(HEADER) libft/libft.h
	@gcc -c $(CFLAGS) $<  -o $@ 
	@printf "\033[0;32m[compiling : %-30s .....\] \r" ${notdir $@}

$(NAME): $(OBJS) $(HEADER)
	make bonus -C libft
	gcc minishell.c -I/path/to/readline/include -lreadline -o $(NAME) $(OBJS) libft/libft.a

clean:
	$(RM) $(OBJS) $(OBJS)
	make clean -C libft
	@printf "\033[0;32mCLEANED 🗑️\n"

fclean:clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.SILENT : $(NAME) clean fclean re

.PHONY : all clean fclean re