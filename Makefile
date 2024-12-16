# **************************************************************************** #
#									      #
#							 :::      ::::::::    #
#    Makefile					   :+:      :+:    :+:    #
#						     +:+ +:+	 +:+      #
#    By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+	 #
#						 +#+#+#+#+#+   +#+	    #
#    Created: 2024/12/16 23:00:00 by peda-cos	  #+#    #+#	      #
#    Updated: 2024/12/16 23:59:59 by peda-cos	 ###   ########.fr	#
#									      #
# **************************************************************************** #

NAME        =   fdf

LIBFT_DIR   =   lib/libft
LIBFT       =   $(LIBFT_DIR)/libft.a

MLX42_DIR   =   lib/MLX42
MLX42       =   $(MLX42_DIR)/build/libmlx42.a

INC_DIR     =   inc
SRC_DIR     =   src

HEADERS     =   -I ./ -I $(MLX42_DIR)/include -I $(LIBFT_DIR)

SRCS = main.c \
	   fdf.c \
	   parsing.c \
	   draw_grid.c \
	   draw_line.c \
	   color_functions.c \
	   zoom.c \
	   move.c \
	   key_hook.c \
	   memory_functions.c \
	   math_utils.c \
	   helpers.c

OBJ = $(SRCS:.c=.o)

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