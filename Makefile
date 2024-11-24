# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/15 05:35:59 by peda-cos          #+#    #+#              #
#    Updated: 2024/11/24 14:37:59 by peda-cos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
MLX42_PATH = ./lib/MLX42
MLX42_LIB = $(MLX42_PATH)/build/libmlx42.a -lglfw -lm -lpthread -ldl
LIBFT_PATH = ./lib/libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a

INCLUDES = -I./include -I$(MLX42_PATH)/include -I$(LIBFT_PATH)/include

SRC_DIR	= src
SRCS	= $(SRC_DIR)/main.c $(SRC_DIR)/parse.c $(SRC_DIR)/utils.c \
		  $(SRC_DIR)/event.c $(SRC_DIR)/render.c

OBJ_DIR	= obj
OBJS	= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_PATH)
	@cmake -S $(MLX42_PATH) -B $(MLX42_PATH)/build
	@make -C $(MLX42_PATH)/build
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT_LIB) $(MLX42_LIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/src

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_PATH)
	make clean -C $(MLX42_PATH)/build

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)
	rm -rf $(MLX42_PATH)/build

re: fclean all
