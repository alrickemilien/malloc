#include "malloc.h"

static void put_addr(void *param)
{
	const char		*str = "0123456789ABCDEF";
	int				i;
	size_t			ptr;
	size_t			n;

	ptr = (size_t)param;
	n = 0xF000000000000000;
	i = 60;
	write(1, "0x", 2);
	while (!((ptr & n) >> i))
	{
		n >>= 4;
		i -= 4;
	}
	while (n)
	{
		write(1, str + ((ptr & n) >> i), 1);
		n >>= 4;
		i -= 4;
	}
}

void	free(void *ptr)
{
	t__malloc_block__					*block;
	extern struct s__malloc_instance__	g__malloc_instance__;

	if (!ptr)
		return;
	block = (t__malloc_block__*)ptr - 1;
	put_addr(ptr);
	write(1, "\n", 1);
	block->is_free = 1;
	ft_putendl("FREE CALLED");
	if (block->size > __MALLOC_SMALL_LIMIT__)
	{
		if (g__malloc_instance__.options.malloc_env_vars[MallocScribble])
			ft_memset(ptr, 0x55, (size_t)block->size);
		munmap(block,
				(size_t)block->size + sizeof(t__malloc_block__));
	}
	else
	{
		if (g__malloc_instance__.options.malloc_env_vars[MallocScribble])
			ft_memset(ptr, 0x55, (size_t)block->size);
	}
	return ;
}
