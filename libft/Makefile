# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pepinhei <pepinhei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/15 11:21:33 by pepinhei          #+#    #+#              #
#    Updated: 2025/08/15 11:21:34 by pepinhei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a 

CC = cc 

CFLAGS = -Wall -Wextra -Werror -g3

FILES = ft_atoi.c\
ft_isdigit.c\
ft_memmove.c\
ft_strchr.c\
ft_strrchr.c\
ft_bzero.c\
ft_isprint.c\
ft_memset.c\
ft_strdup.c\
ft_tolower.c\
ft_calloc.c\
ft_putchar_fd.c\
ft_strlcat.c\
ft_toupper.c\
ft_isalnum.c\
ft_memchr.c\
ft_putendl_fd.c\
ft_strlcpy.c\
ft_isalpha.c\
ft_memcmp.c\
ft_strlen.c\
ft_isascii.c\
ft_memcpy.c\
ft_putstr_fd.c\
ft_strncmp.c\
ft_strmapi.c\
ft_striteri.c\
ft_strjoin.c\
ft_putnbr_fd.c\
ft_substr.c\
ft_strnstr.c\
ft_split.c\
ft_strtrim.c\
ft_itoa.c


OUTPUTS := $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OUTPUTS)
	ar rcs $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean: 
	rm -rf *.o	

fclean: clean 
	rm -rf $(NAME)

re: fclean all	
	
 