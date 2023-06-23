# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oaboulgh <oaboulgh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/01 16:42:01 by oaboulgh          #+#    #+#              #
#    Updated: 2023/06/06 16:20:56 by oaboulgh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

SRCS		= ft_printf.c \
			  ft_puts.c \
			  ft_format.c \
			  
			  

OBJS		= $(SRCS:%.c=%.o)

INCS		= ft_printf.h

FLAGS		= -Wall -Werror -Wextra  #-g #-fsanitize=address

all: $(NAME)

%.o : %.c $(INCS)
	@cc $(CFLAGS) -c $< -o $@
	@printf "\033[0;32m[compiling : %-30s .....\] \r" ${notdir $@}

$(NAME):$(OBJS)
	@ar rc $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)
	
fclean: clean
	@rm -f $(NAME)

re: fclean all

.SILENT : $(NAME) clean fclean re

.PHONY: all re clean fclean