NAME = minishell

SRC = minishell.c handle_signals.c commandList.c commandExec.c

OBJ = ${SRC:.c=.o}

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@echo "linking objects"
	$(MAKE) -C ./libft
	gcc $(OBJ) -o $@ -L./libft -lft -L/usr/include -lreadline

%.o: %.c
	@echo "compiling source files"
	$(CC) -c $< -o $@ -I./
clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)