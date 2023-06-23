# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 18:01:35 by melsahha          #+#    #+#              #
#    Updated: 2023/06/23 14:36:54 by melsahha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parse
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INC = -I./include
LINK = -L. -lftprintf -lreadline
LIBFT = libftprintf.a
LIBFT_DIR = ../../libft/

OBJ_DIR = ./obj
SRC = main.c check_input.c input_utils.c \
	tokens.c split.c split_utils.c check_split.c \
	expand_quotes.c expand_env.c \
	sort_tokens.c token_utils.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

$(NAME): $(OBJ) $(OBJ_DIR)
	make -sC $(LIBFT_DIR)
	mv $(LIBFT_DIR)$(LIBFT) .
	$(CC) $(CFLAGS) $(OBJ) $(LINK) -o $(NAME)

all: $(NAME)

$(OBJ_DIR)/%.o:%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(INCL) $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)
	make -sC $(LIBFT_DIR) clean
	rm -f $(LIBFT)

fclean: clean
	rm -f $(NAME)

re: fclean all

phone: re clean fclean $(NAME)
