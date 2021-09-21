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

fclean: clean
	@rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)