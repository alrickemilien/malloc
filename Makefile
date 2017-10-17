ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

ifeq ($(OS),)
	OS := $(shell uname -s)
endif

ifeq ($(OS),"Linux")
	LD_LIBRARY_PATH := $(LD_LIBRARY_PATH):$(HOME)/malloc
endif

NAME=libft_malloc_$(HOSTTYPE).so

CCFLAGS= -Wall -Wextra -Werror 

DIR_LIBFT=libft

LIBFT= -lft -L $(DIR_LIBFT) -I $(DIR_LIBFT)

LPTHREAD= -lpthread

SRC=src/lib.c\
	src/show_alloc_mem.c\
	src/malloc/malloc.c\
	src/free/free.c\
	src/realloc/realloc.c\
	src/print_memory.c\

OBJ=$(SRC:.c=.o)

INCLUDE=-I src/include

.PHONY: all clean fclean


all: $(NAME)

test: all
	@gcc test/main.c libft_malloc.so

$(NAME): $(OBJ)
	@make -C $(DIR_LIBFT)
	@gcc $^ -shared -o $@ $(INCLUDE) \
	$(LIBFT) $(LPTHREAD) $(CCFLAGS)
	@ln -sf $(NAME) libft_malloc.so

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
