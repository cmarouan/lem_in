
NAME = lem-in
SRC = srcs/main.c srcs/ft_bfs.c srcs/ft_pass_ants.c srcs/ft_choosegroup.c \
		srcs/ft_path.c srcs/ft_queue.c srcs/ft_free.c srcs/ft_parse.c \
		srcs/ft_line.c srcs/ft_init.c srcs/ft_node.c srcs/ft_math.c \
		srcs/ft_tools.c gnl/gnl.c
CFLAG = -Wall -Wextra -Werror
INC = includes


OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME): $(OBJ)
	make -C libft/
	gcc -o $(NAME) $(OBJ) -L libft -lft

$(OBJ) : %.o : %.c
		gcc $(CFLAG) -o $@ -c $< -I $(INC) 

clean:
	make -C libft/ clean
	rm -rf $(OBJ)

fclean:clean
	make -C libft/ fclean
	rm -rf $(NAME) 

re: fclean $(NAME)

c:
	#make -C libft/

	gcc $(CFLAG) main.c srcs/ft_node.c srcs/ft_line.c srcs/ft_tools.c\
		srcs/ft_bfs.c srcs/ft_queue.c srcs/ft_path.c\
		 -L libft -lft -I $(INC)
