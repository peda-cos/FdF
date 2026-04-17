# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/08 00:00:00 by peda-cos          #+#    #+#              #
#    Updated: 2026/04/09 00:00:00 by peda-cos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = libft.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I.

# ── libft core ──────────────────────────────────────────────────────────────
LIBFT_SRCS = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

# ── ft_printf (bonus – all flags: -0.# +space, width, precision) ────────────
PRINTF_DIR  = ft_printf/bonus
PRINTF_SRCS = \
	$(PRINTF_DIR)/ft_printf_bonus.c \
	$(PRINTF_DIR)/parse_format_bonus.c \
	$(PRINTF_DIR)/dispatch_bonus.c \
	$(PRINTF_DIR)/convert_char_bonus.c \
	$(PRINTF_DIR)/convert_int_bonus.c \
	$(PRINTF_DIR)/convert_uint_bonus.c \
	$(PRINTF_DIR)/convert_ptr_bonus.c \
	$(PRINTF_DIR)/utils_write_bonus.c \
	$(PRINTF_DIR)/utils_nbr_bonus.c

# ── get_next_line (bonus – multi-fd support) ────────────────────────────────
GNL_DIR  = get_next_line
GNL_SRCS = \
	$(GNL_DIR)/get_next_line_bonus.c \
	$(GNL_DIR)/get_next_line_utils_bonus.c

# ── aggregate ────────────────────────────────────────────────────────────────
SRCS = $(LIBFT_SRCS) $(PRINTF_SRCS) $(GNL_SRCS)
OBJS = $(SRCS:.c=.o)

# ── rules ────────────────────────────────────────────────────────────────────
all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "Compiled: $(NAME)"

# generic rule – handles files in subdirectories
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling: $<"

# ft_printf bonus headers live inside the subdir; add -I flag for them
$(PRINTF_DIR)/%.o: $(PRINTF_DIR)/%.c
	@$(CC) $(CFLAGS) -I$(PRINTF_DIR) -c $< -o $@
	@echo "Compiling: $<"

$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
	@$(CC) $(CFLAGS) -I$(GNL_DIR) -c $< -o $@
	@echo "Compiling: $<"

bonus: $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "Cleaned: objects"

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned: $(NAME)"

re: fclean all

.PHONY: all clean fclean re bonus
