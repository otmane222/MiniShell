# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 16:32:50 by oaboulgh          #+#    #+#              #
#    Updated: 2023/03/30 14:28:45 by oaboulgh         ###   ########.fr        #
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

OBJS = $(SRCS:.c=.o)

CFLAGS = #-Wall -Wextra -Werror

HEADER = minishell.h \
	tokenizer/tokenizer.h

RM = rm -rf

all: $(NAME) $(OBJS) $(HEADER)
	@printf "\033[0;32mDONE ✅"

%.o: %.c $(HEADER) libft/libft.h
	@cc -c $(CFLAGS) $<  -o $@ 
	@printf "\033[0;32m[compiling : %-30s .....\] \r" ${notdir $@}

$(NAME): $(OBJS) $(HEADER)
	make bonus -C libft
	cc minishell.c -lreadline -o $(NAME) $(OBJS) libft/libft.a

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