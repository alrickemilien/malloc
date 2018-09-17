ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

ifeq ($(OS),)
	OS := $(shell uname -s)
endif

SO_OPTIONS	:= -shared

ifeq ($(OS),Linux)
	LD_LIBRARY_PATH	:= $(LD_LIBRARY_PATH):$(HOME)/Projects/malloc
	OBJ_OPTIONS	:= -fPIC
	SO_OPTIONS	= -shared -Wl,-soname,
endif

NAME= libft_malloc_$(HOSTTYPE).so

CCFLAGS= -Wall -Wextra -Werror

DIR_LIBFT= libft

LPTHREAD= -lpthread

LIBFT= -lft -L $(DIR_LIBFT) -I $(DIR_LIBFT)


SRC=src/utils.c \
	src/show_alloc_mem.c \
	src//malloc.c \
	src//free.c \
	src/calloc.c \
	src/realloc.c \
	src/print_memory.c \
	src/put_addr.c \
	src/get_zone.c \

OBJ=$(SRC:.c=.o)

INCLUDE=-I src/include

.PHONY: all clean fclean

all: $(NAME)

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
