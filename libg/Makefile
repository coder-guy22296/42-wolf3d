# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cyildiri <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/02 13:05:49 by cyildiri          #+#    #+#              #
#    Updated: 2016/10/02 13:05:49 by cyildiri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgraphics
SRC =   add_object.c\
		color.c\
		window.c\
		frame.c\
		camera.c\
		del_3d_object.c\
		del_renderer.c\
		del_scene.c\
		drawline.c\
		drawline3d.c\
		perspective_projection.c\
		orthographic_projection.c\
		frame_pixel_put.c\
		rem_object.c\
		render3d_object.c\
		render_scene.c\
		renderer.c\
		rotate_object.c\
		scene.c\
		translate_point.c\
		update_verticies.c\
		vec2f.c\
		vec2i.c\
		vec3f.c\
		vec6f.c\

OFILES = $(SRC:.c=.o)

#   Edit path to library
LIBFT = ../libft/
MLX = ../minilibx/

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror -I $(LIBFT) -I $(MLX) -c $(SRC)
	ar rc $(NAME).a $(OFILES)
	ranlib $(NAME).a

clean:
	rm -rf $(OFILES)

fclean: clean
	rm -f $(NAME).a

re: fclean all

precom:
	make -C $(LIBFT)

norm:
	norminette $(SRC) $(NAME).h
