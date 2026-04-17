# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/25 00:00:00 by peda-cos          #+#    #+#              #
#    Updated: 2026/03/25 00:00:00 by peda-cos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = src/ft_printf.c src/parse_format.c src/dispatch.c src/convert_char.c src/convert_int.c \
       src/convert_uint.c src/convert_ptr.c src/utils_write.c src/utils_nbr.c
OBJS = $(SRCS:.c=.o)
BONUS_SRCS = bonus/ft_printf_bonus.c bonus/parse_format_bonus.c bonus/dispatch_bonus.c \
             bonus/convert_char_bonus.c bonus/convert_int_bonus.c bonus/convert_uint_bonus.c \
             bonus/convert_ptr_bonus.c bonus/utils_write_bonus.c bonus/utils_nbr_bonus.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "Compiled: $(NAME)"

src/%.o: src/%.c src/ft_printf.h
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling: $<"

bonus: .bonus

.bonus: $(BONUS_OBJS)
	@ar rcs $(NAME) $(BONUS_OBJS)
	@touch .bonus
	@echo "Compiled: $(NAME) (bonus)"

bonus/%_bonus.o: bonus/%_bonus.c bonus/ft_printf_bonus.h
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling: $<"

clean:
	@rm -f $(OBJS) $(BONUS_OBJS) .bonus
	@echo "Cleaned: $(OBJS) $(BONUS_OBJS)"

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned: $(NAME)"

re: fclean all

.PHONY: all clean fclean re bonus
