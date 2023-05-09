# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 18:01:35 by melsahha          #+#    #+#              #
#    Updated: 2023/05/09 18:51:41 by melsahha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parse
CC = cc
CFLAGS = -Wall -Wextra -Werror

INC = -I./include
LINK = -L. -lftprintf -lreadline
LIBFT = libftprintf.a
LIBFT_DIR = ../libft/

SRC_DIR = ./src/
OBJ_DIR = ./obj
SRC_FILES = main.c list.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

$(NAME): $(OBJ) $(OBJ_DIR)
	make -C $(LIBFT_DIR)
	mv $(LIBFT_DIR)$(LIBFT) .
	$(CC) $(CFLAGS) $(OBJ) $(LINK) -o $(NAME)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(INCL) $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)
	make -sC $(PRINTF_DIR) clean
	rm -f $(PRINTF_LIB)

fclean: clean
	rm -f $(NAME)

re: fclean all

phone: re clean fclean $(NAME)
