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

NAME        =   fdf

LIBFT_DIR   =   lib/libft
LIBFT       =   $(LIBFT_DIR)/libft.a

MLX42_DIR   =   lib/MLX42
MLX42       =   $(MLX42_DIR)/build/libmlx42.a

SRC_DIR     =   src
SRC         =   \
				$(SRC_DIR)/color_mapping.c $(SRC_DIR)/error_handling.c \
				$(SRC_DIR)/line_render.c $(SRC_DIR)/math_utils.c \
				$(SRC_DIR)/mesh_rendering.c $(SRC_DIR)/reader_loop.c \
				$(SRC_DIR)/triangle_rendering.c $(SRC_DIR)/vector_operations.c \
				$(SRC_DIR)/color_operations.c $(SRC_DIR)/event_handlers.c \
				$(SRC_DIR)/line_rendering.c $(SRC_DIR)/mesh_initializer.c \
				$(SRC_DIR)/pixel_rendering.c $(SRC_DIR)/skybox_projection.c \
				$(SRC_DIR)/ui_controls.c $(SRC_DIR)/cursor_handling.c \
				$(SRC_DIR)/fdf.c $(SRC_DIR)/map_reader.c \
				$(SRC_DIR)/mesh_projection.c $(SRC_DIR)/png_parser.c \
				$(SRC_DIR)/skybox_rendering.c $(SRC_DIR)/validation_utils.c

OBJ_DIR     =   obj
OBJ         =   $(SRC:%.c=$(OBJ_DIR)/%.o)

CC          =   cc
CFLAGS      =   -Wall -Wextra -Werror -Ofast
LDFLAGS     =   -lm -ldl -lglfw -flto

all: $(LIBFT) $(MLX42) $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX42)
	$(CC) $(OBJ) $(LIBFT) $(MLX42) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX42):
	@echo "Cloning MLX42..."
	cd lib && git clone https://github.com/codam-coding-college/MLX42.git
	cmake -B $(MLX42_DIR)/build -S $(MLX42_DIR)
	make -C $(MLX42_DIR)/build -j4

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(NAME) $(MLX42_DIR)

re: fclean all

.PHONY: all clean fclean re