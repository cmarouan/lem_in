
NAME = lem
SRC = srcs/main.c srcs/ft_bfs.c srcs/ft_pass_ants.c srcs/ft_choosegroup.c \
		srcs/ft_path.c srcs/ft_queue.c srcs/ft_free.c srcs/ft_parse.c \
		srcs/ft_line.c srcs/ft_init.c srcs/ft_node.c srcs/ft_math.c \
		srcs/ft_tools.c
CFLAG = -Wall -Wextra -Werror
INC = includes

test2:
	gcc $(CFLAG) srcs/allpathbfs.c

t:
	gcc $(CFLAG) srcs/bfs.c

c:
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
