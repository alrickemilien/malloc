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

void	show_alloc_mem()
{
	extern struct s__malloc_instance__	g__malloc_instance__;
	t__malloc_block__					*ptr;

	ptr = g__malloc_instance__.tiny_zone;
	ft_putstr("TINY : ");
	put_addr(g__malloc_instance__.tiny_zone_addr.addr);
	while (ptr)
	{
		write(1, "\n", 1);
		if (!ptr->is_free)
		{
			write(1, "\n", 1);
			put_addr(ptr + 1);
			ft_putstr(" - ");
			put_addr(((void*)(ptr + 1) + (size_t)ptr->size));
			write(1, "\n", 1);
			print_memory(ptr, sizeof(t__malloc_block__) + ptr->size);
		}
		ptr = ptr->next;
	}
}
