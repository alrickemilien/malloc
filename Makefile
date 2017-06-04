ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME=libft_malloc_$(HOSTTYPE).so

CCFLAGS= -Wall -Wextra -Werror 

DIR_LIBFT=libft

LIBFT= -lft -L $(DIR_LIBFT) -I $(DIR_LIBFT)

LPTHREAD= -lpthread

SRC= src/lib.c\
	 src/malloc/malloc.c\
	 src/free/free.c\
	 src/realloc/realloc.c

OBJ=$(SRC:.c=.o)

INCLUDE=-I src/include

.PHONY: all clean fclean

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(DIR_LIBFT)
	@gcc $^ -shared -o $@ $(INCLUDE)\
	$(LIBFT) $(LPTHREAD) $(CCFLAGS)
	@ln -s $(NAME) libft_malloc.so

%.o: %.c
	@gcc -o $@ -c $< $(INCLUDE) $(CCFLAGS)

clean:
	@make clean -C $(DIR_LIBFT)
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C $(DIR_LIBFT)
	@rm -rf $(NAME)
	@rm -rf libft_malloc.so

re: fclean all
