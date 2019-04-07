# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmoussai <khalidmossaid@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/06 10:05:26 by kmoussai          #+#    #+#              #
#    Updated: 2018/10/17 09:55:20 by kmoussai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_lstnew.c		ft_putstr.c			ft_strmapi.c\
	  ft_memalloc.c		ft_putstr_fd.c		ft_strncat.c\
	  ft_atoi.c			ft_memccpy.c		ft_strcat.c\
	  ft_strncmp.c		ft_bzero.c			ft_memchr.c\
	  ft_strchr.c		ft_strncpy.c		ft_digitcount.c\
	  ft_memcmp.c		ft_strclr.c			ft_strnequ.c\
	  ft_isalnum.c		ft_memcpy.c			ft_strcmp.c\
	  ft_strnew.c		ft_isalpha.c		ft_memdel.c	\
  	  ft_strcpy.c		ft_strnstr.c		ft_isascii.c\
	  ft_memmove.c		ft_strdel.c			ft_strrchr.c\
	  ft_isdigit.c		ft_memset.c			ft_strdup.c\
	  ft_strsplit.c		ft_isprint.c		ft_nextindexof.c\
	  ft_strequ.c		ft_strstr.c			ft_itoa.c\
	  ft_putchar.c		ft_striter.c		ft_strsub.c\
	  ft_lstadd.c		ft_putchar_fd.c		ft_striteri.c\
	  ft_strtrim.c		ft_lstdel.c			ft_putendl.c\
	  ft_strjoin.c		ft_tolower.c		ft_lstdelone.c\
	  ft_putendl_fd.c	ft_strlcat.c		ft_toupper.c\
	  ft_lstiter.c		ft_putnbr.c			ft_strlen.c	\
	  ft_wordcount.c	ft_lstmap.c			ft_putnbr_fd.c\
	  ft_strmap.c		ft_sort_integer_table.c	ft_swap.c

HEADERS = libft.h

OBJ = *.o 

CFLAG = -Wall -Wextra -Werror

NAME = libft.a

all: $(NAME) 

$(NAME):
	gcc -c $(CFLAG) $(SRC)
	ar rc $(NAME) $(OBJ) $(HEADERS)
	ranlib	$(NAME)
clean:
	/bin/rm -f $(OBJ)
fclean: clean
	/bin/rm -f libft.a
re: fclean all
