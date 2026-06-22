NAME = minishell

CC = cc

CFLAGS = -g -Ilibft -Iincludes

all:
	make -C libft
	$(CC) $(CFLAGS) src/*.c libft/libft.a -lreadline -o $(NAME)

clean:
	make -C libft clean

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

