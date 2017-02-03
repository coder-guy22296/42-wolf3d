#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/08 19:17:08 by cyildiri          #+#    #+#              #
#    Updated: 2016/11/08 19:17:11 by cyildiri         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = wolf3d
SRC =   wolf3d.c
OFILES = $(SRC:.c=.o)

LIBFT = libft/
MLX = minilibx/
LIBG = libg/

LIBS = -L $(LIBFT) -lft
LIBS += -L $(MLX) -lmlx -framework OpenGL -framework AppKit
LIBS += -L $(LIBG) -lgraphics

LIBI = -I $(LIBFT)
LIBI += -I $(MLX)
LIBI += -I $(LIBG)

all: $(NAME)

$(NAME): dependencies
	gcc -Wall -Wextra -Werror -c $(SRC) $(LIBI)
	gcc -o $(NAME) $(OFILES) $(LIBS)

clean:
	rm -rf $(OFILES)
	make -C $(MLX) clean
	make -C $(LIBG) clean
	make -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBG) fclean
	make -C $(LIBFT) fclean

re: fclean all

dependencies:
	make -C $(MLX)
	make -C $(LIBFT)
	make -C $(LIBG)

test:
	rm -f $(NAME)
	rm -rf $(OFILES)
	gcc -Wall -Wextra -Werror -c $(SRC) $(LIBI)
	gcc -o $(NAME) $(OFILES) $(LIBS)

norm:
	norminette *.c *.h ./lib*/*.c ./lib*/*.h