# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: johnduro <>                                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/28 11:39:35 by johnduro          #+#    #+#              #
#    Updated: 2014/01/28 11:39:35 by johnduro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=select
VERSION=1.0.0
CFLAGS=-Wall -Werror -Wextra -g
INCLUDES=-I ./libft/includes -L /usr/lib
LIBS=./libft/libft.a

SRC=ft_error.c \
	ft_select.c \
	se_delelem.c \
	se_end.c \
	se_feat.c \
	se_move.c \
	se_operations.c \
	se_print.c \
	se_set_arg.c \
	se_signal.c \
	se_singleton.c \
	sig_kill.c \

OBJ=$(SRC:.c=.o)

all: build $(NAME) finish

build:
	@($(MAKE) -C ./libft)

$(NAME): $(OBJ)
	gcc $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBS)  -ltermcap -lncurses

%.o: %.c ft_select.h ./libft/includes
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $< -L /usr/lib -ltermcap -lncurses

clean:
	@(rm -rf $(OBJ))

fclean: clean
	@(rm -rf $(NAME))
	@($(MAKE) -C ./libft fclean)

re: fclean all

v:
	@(echo "version: $(VERSION)")

finish:
	@(echo "[\\\\033[32m$(NAME)\\\\033[00m]")

.PHONY: all build clean fclean re v
