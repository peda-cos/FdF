# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+      #
#    By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/15 05:35:59 by peda-cos          #+#    #+#              #
#    Updated: 2024/12/13 12:00:00 by peda-cos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        =   fdf

LIBFT_DIR   =   lib/libft
LIBFT       =   $(LIBFT_DIR)/libft.a

MLX42_DIR   =   lib/MLX42
MLX42       =   $(MLX42_DIR)/build/libmlx42.a

INC_DIR     =   inc
SRC_DIR     =   src

HEADERS     =   -I $(INC_DIR) -I $(MLX42_DIR)/include -I $(LIBFT_DIR)

SRC         =   $(SRC_DIR)/color_functions.c $(SRC_DIR)/fdf.c \
				$(SRC_DIR)/key_hook.c $(SRC_DIR)/math_utils.c $(SRC_DIR)/move.c \
				$(SRC_DIR)/zoom.c $(SRC_DIR)/draw_line.c \
				$(SRC_DIR)/main.c $(SRC_DIR)/memory_functions.c \
				$(SRC_DIR)/parsing.c

OBJ         =   $(SRC:%.c=%.o)

CC          =   cc
CFLAGS      =   -Wall -Wextra -Werror -Ofast $(HEADERS)
LDFLAGS     =   -lm -ldl -lglfw -pthread -flto

all: $(LIBFT) $(MLX42) $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX42)
	@$(CC) $(OBJ) $(LIBFT) $(MLX42) -o $(NAME) $(LDFLAGS)
	@echo "Executable $(NAME) created!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling $<"

$(MLX42):
	@echo "Cloning and building MLX42..."
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		cd lib && git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	@cmake -B $(MLX42_DIR)/build -S $(MLX42_DIR)
	@make -C $(MLX42_DIR)/build -j4

$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "Cleaning object files..."
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ)

fclean: clean
	@echo "Cleaning all files..."
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME) $(MLX42_DIR)

re: fclean all

.PHONY: all clean fclean re
