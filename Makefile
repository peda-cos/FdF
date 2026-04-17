# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#              #
#    Updated: 2026/04/16 00:00:00 by peda-cos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = fdf
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I./include -I./libft -I./libft/get_next_line -I./minilibx
LDFLAGS = -L./libft -lft -L./minilibx -lmlx_Linux -lXext -lX11 -lm

# ── sources ──────────────────────────────────────────────────────────────────
SRCS = src/main.c src/parse_map.c src/parse_utils.c src/init.c \
       src/render.c src/project.c src/draw_line.c src/color.c \
       src/hooks.c src/cleanup.c

OBJS = $(SRCS:.c=.o)

# ── rules ────────────────────────────────────────────────────────────────────
all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C libft
	@$(MAKE) -C minilibx
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "Compiled: $(NAME)"

src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling: $<"

bonus: $(NAME)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C libft clean
	@echo "Cleaned: objects"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean
	@echo "Cleaned: $(NAME)"

re: fclean all

.PHONY: all clean fclean re
