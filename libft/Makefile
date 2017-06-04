# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aemilien <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/16 11:45:00 by aemilien          #+#    #+#              #
#    Updated: 2017/05/14 15:03:14 by aemilien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CCFLAGS= -Wall -Wextra -Werror

SRC= ft_isdigit.c ft_memcpy.c ft_putendl_fd.c ft_strclr.c ft_striteri.c ft_strncmp.c\
	 ft_strstr.c ft_isprint.c ft_memdel.c ft_putnbr.c ft_strcmp.c ft_strjoin.c \
	 ft_strncpy.c ft_strsub.c ft_atoi.c ft_itoa.c ft_memmove.c ft_putnbr_fd.c \
	 ft_strcpy.c ft_strlcat.c ft_strnequ.c ft_strtrim.c ft_bzero.c ft_memalloc.c \
	 ft_memset.c ft_putstr.c ft_strdel.c ft_strlen.c ft_strnew.c ft_tolower.c \
	 ft_isalnum.c ft_memccpy.c ft_putchar.c ft_putstr_fd.c ft_strdup.c ft_strmap.c \
	 ft_strnstr.c ft_toupper.c ft_isalpha.c ft_memchr.c ft_putchar_fd.c ft_strcat.c \
	 ft_strequ.c ft_strmapi.c ft_strrchr.c ft_isascii.c ft_memcmp.c ft_putendl.c \
	 ft_strchr.c ft_striter.c ft_strncat.c ft_strsplit.c ft_lstadd.c ft_lstdel.c \
	 ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_lstlen.c \
	 get_next_line.c ft_ltoa.c ft_dtoa.c ft_power.c ft_strrepeat.c recycle.c\
	 ft_char_to_str.c ft_strupcase.c ft_strsplice.c\

OBJ=$(SRC:.c=.o)

NAME=libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

%.o: %.c
	@gcc -o $@ -c $< $(CCFLAGS)

clean:
	@rm -rf $(OBJ)

.PHONY: clean fclean 

fclean: clean
	@rm -rf $(NAME)

re: fclean all
