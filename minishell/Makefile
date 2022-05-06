# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbarbit <cbarbit@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/06 11:28:34 by cbarbit           #+#    #+#              #
#    Updated: 2022/05/06 14:44:36 by cbarbit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

C_FILES =	srcs/minishell.c \
			srcs/prompt.c \
			srcs/lexer.c \
			srcs/processes.c \

CC = cc

CFLAGS = -Werror -Wall -Wextra

RM = rm -f

O_FILES = ${C_FILES:.c=.o}

all: ${NAME}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

${NAME} : ${O_FILES}
	@${MAKE} -C libft
	@${CC} ${O_FILES} -lreadline libft/libft.a -o ${NAME}


clean:
	@${RM} ${O_FILES}

fclean: clean
	@make fclean -C libft
	@${RM} ${NAME}


re: fclean all

.PHONY: all clean fclean re