ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

ifeq ($(OS),)
	OS := $(shell uname -s)
endif

SO_OPTIONS	:= -shared

DIR_MALLOC= $(HOME)/Projects/malloc

ifeq ($(OS),Linux)
	LD_LIBRARY_PATH	:= $(LD_LIBRARY_PATH):$(DIR_MALLOC)
	OBJ_OPTIONS	:= -fPIC
	SO_OPTIONS	= -shared -Wl,-soname,
endif

CCFLAGS= -Wall -Wextra -Werror

# Libft in the malloc directory
DIR_LIBFT= ../libft

LPTHREAD= -lpthread

LIBFT= -lft -L $(DIR_LIBFT) -I $(DIR_LIBFT)

SRC=src/test1.c\
	src/test2.c\
	src/test3.c\
	src/test4.c\
	src/test5.c

.PHONY: all env clean fclean

all: env $(SRC)

env: 
	mkdir -p bin
	@make -C $(DIR_MALLOC)
	@make -C $(DIR_LIBFT)

%.c:
	@gcc $^ -o bin/$@ $(INCLUDE) $(LPTHREAD) $(CCFLAGS) $(OBJ_OPTIONS)

clean:
	@make clean -C $(DIR_LIBFT)
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C $(DIR_LIBFT)
	@rm -rf ./bin

re: fclean all
