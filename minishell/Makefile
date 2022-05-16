# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/06 11:28:34 by cbarbit           #+#    #+#              #
#    Updated: 2022/05/11 16:14:02 by cbarbit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

C_FILES =	srcs/minishell.c \
			srcs/lexer_all.c \
			srcs/processes.c \
			srcs/env_lst.c \
			srcs/mallocs.c \
			srcs/signals_handlers.c \
			srcs/init_tokens.c \
			srcs/copy_tokens.c \
			srcs/manage_tokens.c			

CC = cc

CFLAGS = -Werror -Wall -Wextra -g

RM = rm -f

O_FILES = ${C_FILES:.c=.o}

all: ${NAME}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

${NAME} : ${O_FILES}
	@${MAKE} -C libft
	@${CC} ${O_FILES} -lreadline libft/libft.a -g -o ${NAME}


clean:
	@${RM} ${O_FILES}

fclean: clean
	@make fclean -C libft
	@${RM} ${NAME}


re: fclean all

.PHONY: all clean fclean re