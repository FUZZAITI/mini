NAME = minishell

CC = cc

CFLAGS = -Ilibft -Iincludes

SRC =	src/*.c \
		src/built_in/*.c \
		src/cmd/*.c \
		src/env/*.c \
		src/execute/*.c \
		src/expander/*.c \
		src/free/*.c \
		src/lexer/*.c

all:
	make -C libft
	$(CC) $(CFLAGS) $(SRC) libft/libft.a -lreadline -o $(NAME)

clean:
	make -C libft clean

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
