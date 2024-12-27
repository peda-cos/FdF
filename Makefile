NAME        = fdf
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

LIBFT_DIR   = lib/libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX42_DIR   = lib/MLX42
MLX42       = $(MLX42_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

HEADERS     = -I $(LIBFT_DIR) -I $(MLX42_DIR)/include -I ./src

SRCS        = src/color_utils.c \
              src/line_drawing.c \
              src/line_parameters.c \
              src/map_manager.c \
              src/parse_map_utils.c \
              src/line_drawing_utils.c \
              src/main.c \
              src/parse_map.c \
              src/transformations.c

OBJS        = $(SRCS:.c=.o)

all: $(LIBFT) $(MLX42) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX42) -o $(NAME) $(HEADERS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX42):
	@cd lib && git clone https://github.com/codam-coding-college/MLX42.git || true
	@cmake -S $(MLX42_DIR) -B $(MLX42_DIR)/build
	@$(MAKE) -C $(MLX42_DIR)/build -j4

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@rm -rf $(MLX42_DIR)

re: fclean all

.PHONY: all clean fclean re
