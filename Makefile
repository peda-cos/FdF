# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/15 05:35:59 by peda-cos          #+#    #+#              #
#    Updated: 2024/11/28 00:58:20 by peda-cos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror -ggdb3
MLX42_PATH = ./lib/MLX42
MLX42 = $(MLX42_PATH)/build/libmlx42.a
LIBFT_PATH = ./lib/libft
LIBFT = $(LIBFT_PATH)/libft.a
INCLUDES = -I./include -I$(MLX42_PATH)/include -I$(LIBFT_PATH)/include
LIBS = -L$(LIBFT_PATH) -lft $(MLX42_PATH)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRC = src/main.c src/draw.c src/error.c src/parse.c \
	  src/utils.c src/hooks.c src/color.c src/rotate.c
OBJS = $(SRCS:%.o=%.c)

all: $(NAME)

$(MLX42): $(MLX42_PATH)
	cmake $(MLX42_PATH) -B $(MLX42_PATH)/build;
	make -C$(MLX42_PATH)/build -j4;

$(LIBFT): $(LIBFT_PATH)
	make -C$(LIBFT_PATH);

$(NAME): $(MLX42) $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(INCLUDES) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDES)

clean:
	rm -rf $(OBJS)
	make clean -C$(LIBFT_PATH)

fclean: clean
	rm $(NAME)
	rm fclean -C$(LIBFT_PATH)
	rm fclean -C$(MLX42_PATH)

re: fclean all

.PHONY: all clean fclean re
