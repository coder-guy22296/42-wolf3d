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

NAME = libft
SRC = ft_memalloc.c ft_strdup.c ft_memccpy.c ft_strequ.c ft_atoi.c ft_memchr.c\
 ft_striter.c ft_bzero.c ft_memcmp.c ft_striteri.c ft_cntwords.c ft_memcpy.c\
  ft_strjoin.c ft_count_digits.c	ft_memdel.c ft_strlcat.c ft_isalnum.c\
   ft_memmove.c ft_strlen.c ft_isalpha.c ft_memset.c ft_strmap.c ft_isascii.c\
    ft_pop_sign.c ft_strmapi.c ft_isdigit.c ft_putchar.c ft_strmerge.c\
     ft_isprint.c ft_putchar_fd.c ft_strncat.c ft_isspace.c ft_putendl.c\
      ft_strncmp.c ft_itoa.c ft_putendl_fd.c ft_strncpy.c ft_lmapadd.c\
       ft_putnbr.c ft_strnequ.c ft_lmapget.c ft_putnbr_fd.c ft_strnew.c\
        ft_lmapnew.c ft_putstr.c ft_strnstr.c ft_lmapremove.c ft_putstr_fd.c\
         ft_strrchr.c ft_lstadd.c ft_stradel.c ft_strsplit.c ft_lstaddend.c\
          ft_strcat.c ft_strstr.c ft_lstdel.c ft_strchr.c ft_strsub.c\
           ft_lstdelone.c ft_strclr.c ft_strtrim.c ft_lstiter.c ft_strcmp.c\
            ft_tolower.c ft_lstmap.c ft_strcpy.c ft_toupper.c ft_lstnew.c\
             ft_strdel.c ft_newbuffer.c ft_strnjoin.c ft_delbuffer.c\
              get_next_line.c
OFILES = ft_memalloc.o ft_strdup.o ft_memccpy.o ft_strequ.o ft_atoi.o\
 ft_memchr.o ft_striter.o ft_bzero.o ft_memcmp.o ft_striteri.o ft_cntwords.o\
  ft_memcpy.o ft_strjoin.o ft_count_digits.o	ft_memdel.o ft_strlcat.o\
   ft_isalnum.o ft_memmove.o ft_strlen.o ft_isalpha.o ft_memset.o ft_strmap.o\
    ft_isascii.o ft_pop_sign.o ft_strmapi.o ft_isdigit.o ft_putchar.o\
     ft_strmerge.o ft_isprint.o ft_putchar_fd.o ft_strncat.o ft_isspace.o\
      ft_putendl.o ft_strncmp.o ft_itoa.o ft_putendl_fd.o ft_strncpy.o\
       ft_lmapadd.o ft_putnbr.o ft_strnequ.o ft_lmapget.o ft_putnbr_fd.o\
        ft_strnew.o ft_lmapnew.o ft_putstr.o ft_strnstr.o ft_lmapremove.o\
         ft_putstr_fd.o ft_strrchr.o ft_lstadd.o ft_stradel.o ft_strsplit.o\
          ft_lstaddend.o ft_strcat.o ft_strstr.o ft_lstdel.o ft_strchr.o\
           ft_strsub.o ft_lstdelone.o ft_strclr.o ft_strtrim.o ft_lstiter.o\
            ft_strcmp.o ft_tolower.o ft_lstmap.o ft_strcpy.o ft_toupper.o\
             ft_lstnew.o ft_strdel.o ft_newbuffer.o ft_strnjoin.o\
              ft_delbuffer.o get_next_line.o
HEADERS = includes\libft.h

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror -c $(SRC)
	ar rc $(NAME).a $(OFILES)
	ranlib $(NAME).a
clean:
	rm -rf $(OFILES)
fclean: clean
	rm -f $(NAME).a
re: fclean all
