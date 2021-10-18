# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/04 06:56:48 by lmartins          #+#    #+#              #
#    Updated: 2021/10/18 14:32:05 by tguimara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c signals.c parser.c executor.c builtin.c builtin2.c \
builtin_utils.c environment_utils.c environment_utils2.c environment_create.c \
tokenizer.c tokenizer_reads.c utils.c free_functions.c parser_utils.c

OBJ = ${SRC:.c=.o}

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@echo "linking objects"
	$(MAKE) -C ./libft
	gcc -g $(OBJ)  -o $@ -L./libft -lft -L/usr/include -lreadline

%.o: %.c
	@echo "compiling source files"
	$(CC) -g -c $< -o $@ -I./
clean:
	@rm -f $(OBJ)
	$(MAKE) -C ./libft clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean all
	$(MAKE) -C ./libft re

run: all
	./$(NAME)