NAME	=	pipex

SRCS	=	pipex.c pipex_run.c libft/libft.a

CC	=	gcc
RM	=	rm -f
FLAGS	= -Wall -Wextra -Werror -fsanitize=address

all: $(NAME)

$(NAME):
	make all -C libft
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
		make clean -C libft
		$(RM) $(NAME)

fclean: clean
		make fclean -C libft
		
re: fclean all

.PHONY: all clean fclean re