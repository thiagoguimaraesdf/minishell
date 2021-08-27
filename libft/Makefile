# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tguimara <tguimara@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/18 17:30:09 by tguimara          #+#    #+#              #
#    Updated: 2021/08/23 15:03:44 by tguimara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = src/ft_memset.c src/ft_bzero.c src/ft_memcpy.c src/ft_memccpy.c src/ft_memmove.c \
src/ft_memchr.c src/ft_memcmp.c src/ft_strlen.c src/ft_strlcpy.c src/ft_strlcat.c \
src/ft_strchr.c src/ft_strrchr.c src/ft_strnstr.c src/ft_strncmp.c src/ft_atoi.c \
src/ft_isalpha.c src/ft_isdigit.c src/ft_isalnum.c src/ft_isascii.c src/ft_isprint.c \
src/ft_toupper.c src/ft_tolower.c src/ft_calloc.c src/ft_strdup.c src/ft_substr.c \
src/ft_strjoin.c src/ft_strtrim.c src/ft_split.c src/ft_itoa.c src/ft_strmapi.c \
src/ft_putchar_fd.c src/ft_putstr_fd.c src/ft_putendl_fd.c src/ft_putnbr_fd.c

SRC_BONUS = src/ft_lstnew.c src/ft_lstadd_front.c src/ft_lstsize.c src/ft_lstlast.c src/ft_lstadd_back.c \
src/ft_lstdelone.c src/ft_lstclear.c src/ft_lstiter.c

SRC_PRINTF = ft_printf/src/ft_printf.c ft_printf/src/ft_printf_utils.c ft_printf/src/ft_printf_utils2.c ft_printf/src/ft_handle_char.c \
ft_printf/src/ft_handle_int.c  ft_printf/src/ft_handle_pointer.c ft_printf/src/ft_handle_str.c ft_printf/src/ft_handle_unsignedint.c \
ft_printf/src/ft_handle_hexa.c ft_printf/src/ft_handle_pointer.c ft_printf/src/ft_handle_formats.c ft_printf/src/ft_handle_percent.c

SRC_GNL = get_next_line/src/get_next_line.c get_next_line/src/get_next_line_utils.c 

OBJECTS = ${SRC:.c=.o}

BONUS_OBJ = $(SRC_BONUS:.c=.o)

PRINTF_OBJ = $(SRC_PRINTF:.c=.o)

GNL_OBJ = $(SRC_GNL:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) $(BONUS_OBJ) $(PRINTF_OBJ) $(GNL_OBJ)
	@ar -rcs $(NAME) $(OBJECTS) $(BONUS_OBJ) $(PRINTF_OBJ) $(GNL_OBJ)
	@ranlib $(NAME)

%.o:%.c
	@gcc -Wall -Wextra -Werror -c $< -o $@ -I./

clean:
	@rm -f $(OBJECTS) $(BONUS_OBJ) $(PRINTF_OBJ) $(GNL_OBJ)

fclean: clean
	@rm -f $(NAME) *.o

re: fclean all
