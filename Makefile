
NAME = lem
SRC = srcs/*.c
CFLAG = -Wall -Wextra -Werror
INC = includes

compile:
	gcc $(CFLAG) $(SRC) -I $(INC) libft/*.c gnl/*.c

all:$(NAME)

$(NAME):
	make -C libft/ re
	gcc -c $(CFLAG) $(SRC) -I $(INC) 
	gcc -o $(NAME) *.o -L libft/ -lft


clean:
	make -C libft/ clean
	rm -Rf *.o

fclean:clean
	make -C libft/ fclean
	rm -Rf $(NAME) 

re: fclean $(NAME)
