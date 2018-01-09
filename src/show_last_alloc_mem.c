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

static inline int get_zone(size_t size)
{
	if (size < __MALLOC_TINY_LIMIT__)
		return (__MALLOC_TINY__);
	if (size < __MALLOC_SMALL_LIMIT__)
		return (__MALLOC_SMALL__);
	return (__MALLOC_LARGE__);
}

void	show_last_alloc_mem()
{
	extern struct s__malloc_instance__	g__malloc_instance__;
	int									i;
	char								*strings[3] = {"TINY", "SMALL", "LARGE"};
	extern void *lastAllocMem;
	t__malloc_block__ *ptr;

	ft_putstr("------------- SHOW_LAST_ALLOC_MEM() -------------\n\n");

	if (!lastAllocMem) return ;

	ptr = (t__malloc_block__*)lastAllocMem;

	i = get_zone(((t__malloc_block__*)lastAllocMem - 1)->size);

	ft_putstr("The last alloc memory has been set in the zone ");
	ft_putstr(strings[i]);
	ft_putstr(" that starts at ");

	if (g__malloc_instance__.zone[i])
	{
		if (i != __MALLOC_LARGE__)
			put_addr(g__malloc_instance__.zone_addr[i]);
		else
			put_addr(g__malloc_instance__.zone[i]);


		ft_putstr("\nThe lastAllocMemory ptr takes this range:\n");
		put_addr(ptr);
		ft_putstr(" - ");
		put_addr(((void*)(ptr) + (size_t)((ptr -1)->size)));
		ft_putstr(" : ");
		ft_putnbr(((ptr -1)->size));
		ft_putstr(" octets\n");
	}

	ft_putstr("Total : ");
	ft_putnbr(sizeof(t__malloc_block__) + ((ptr -1)->size));
	ft_putendl(" octets");
}
