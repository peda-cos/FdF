NAME = fdf
CC = cc
CFLAGS = -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
HEADERS = -I ./src -I ./lib/MLX42/include -I ./lib/libft
LIBFT = ./lib/libft/libft.a
MLX42 = ./lib/MLX42/build
LIBMLX42 = $(MLX42)/libmlx42.a
LIBS = $(LIBMLX42) -ldl -lglfw -pthread -lm

SRCS = src/color_utils.c src/line_drawing.c src/line_parameters.c src/map_manager.c src/parse_map_utils.c src/line_drawing_utils.c src/main.c src/parse_map.c src/transformations.c

OBJS = $(SRCS:.c=.o)

all: libmlx $(LIBFT) $(NAME)

$(LIBFT):
	@make all -C ./lib/libft

libmlx:
	@cmake -DDEBUG=1 ./lib/MLX42 -B $(MLX42) && make -C $(MLX42) -j4

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) $(HEADERS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

clean:
	@rm -rf $(OBJS)
	@make clean -C ./lib/libft
	@rm -rf $(MLX42)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C ./lib/libft

re: fclean all

.PHONY: all clean fclean re libmlx
