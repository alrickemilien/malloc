ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

ifeq ($(OS),)
	OS := $(shell uname -s)
endif

GCC_SO_OPTIONS= -shared

ifeq ($(OS),Linux)
	LD_LIBRARY_PATH	:= $(LD_LIBRARY_PATH):$(HOME)/Projects/malloc
	OBJ_OPTIONS	:= -fPIC
	SO_OPTIONS	:= -shared -Wl,-soname,
endif

NAME= libft_malloc_$(HOSTTYPE).so

CCFLAGS= -Wall -Wextra -Werror

DIR_LIBFT= libft

LPTHREAD= -lpthread

LIBFT= -lft -L $(DIR_LIBFT) -I $(DIR_LIBFT)


SRC=src/utils.c \
	src/show_alloc_mem.c \
	src/malloc/malloc.c \
	src/free/free.c \
	src/calloc/calloc.c \
	src/realloc/realloc.c \
	src/print_memory.c \
	src/show_last_alloc_mem.c \
	src/show_alloc_mem_zone.c \

OBJ=$(SRC:.c=.o)

INCLUDE=-I src/include

.PHONY: all clean fclean

all: $(NAME)

test: all
	@cp libft_malloc.so test/libft_malloc.so
	@gcc $(OBJ_OPTIONS) test/main.c libft_malloc.so $(LIBFT)

$(NAME): $(OBJ)
	@make -C $(DIR_LIBFT)
	@gcc $^ $(SO_OPTIONS) -o $@ $(INCLUDE) \
	$(LIBFT) $(LPTHREAD) $(CCFLAGS)
	@ln -sf $(NAME) libft_malloc.so

%.o: %.c
	@gcc -o $@ -c $< $(INCLUDE) $(CCFLAGS) $(OBJ_OPTIONS)

clean:
	@make clean -C $(DIR_LIBFT)
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C $(DIR_LIBFT)
	@rm -rf $(NAME)
	@rm -rf libft_malloc.so

re: fclean all
