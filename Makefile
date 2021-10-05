# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/04 06:56:48 by lmartins          #+#    #+#              #
#    Updated: 2021/10/04 06:58:21 by lmartins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c signals.c parser.c executor.c builtin.c \
environment.c tokenizer.c

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