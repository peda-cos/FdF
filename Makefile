NAME        = fdf

CC          = cc
CFLAGS      = -Wextra -Wall -Werror -Wunreachable-code -Ofast

INCLUDES    = -I ./src -I ./lib/MLX42/include -I ./lib/libft
LIBFT_DIR   = ./lib/libft
LIBFT       = $(LIBFT_DIR)/libft.a
MLX42_DIR   = ./lib/MLX42
MLX42_BUILD = $(MLX42_DIR)/build
LIBMLX42    = $(MLX42_BUILD)/libmlx42.a
LIBS        = $(LIBMLX42) -ldl -lglfw -pthread -lm

SRCS = src/color_utils.c \
       src/line_drawing.c \
       src/line_parameters.c \
       src/map_manager.c \
       src/parse_map_utils.c \
       src/line_drawing_utils.c \
       src/main.c \
       src/parse_map.c \
       src/transformations.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): libmlx $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LIBS)
	@echo "Linking complete: $(NAME)"

libmlx:
	@cmake -DDEBUG=1 $(MLX42_DIR) -B $(MLX42_BUILD)
	@make -C $(MLX42_BUILD) -j4
	@echo "MLX42 build complete."

$(LIBFT):
	@make -C $(LIBFT_DIR) all
	@echo "Libft build complete."

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiling: $<"

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(MLX42_BUILD)
	@echo "Cleanup complete."

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "Full cleanup complete."

re: fclean all

.PHONY: all clean fclean re libmlx
