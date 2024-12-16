NAME        = fdf
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
LIBFT_DIR   = lib/libft
MLX42_DIR   = lib/MLX42
LIBFT       = $(LIBFT_DIR)/libft.a
MLX42       = $(MLX42_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
HEADERS     = -I $(LIBFT_DIR) -I $(MLX42_DIR)/include
SRCS        = main.c fdf.c parsing.c draw_grid.c draw_line.c color_functions.c \
              zoom.c move.c key_hook.c memory_functions.c math_utils.c helpers.c \
              rotation.c
OBJS        = $(SRCS:.c=.o)

all: $(LIBFT) $(MLX42) $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX42)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX42) -o $(NAME) $(HEADERS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX42):
	cd lib && git clone https://github.com/codam-coding-college/MLX42.git || true
	cmake -S $(MLX42_DIR) -B $(MLX42_DIR)/build
	make -C $(MLX42_DIR)/build -j4

%.o: %.c fdf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -rf $(MLX42_DIR)

re: fclean all

.PHONY: all clean fclean re
