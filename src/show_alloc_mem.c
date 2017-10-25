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

static void		print_zone(t__malloc_block__ *ptr, int *total)
{
	while (ptr)
	{
		write(1, "\n", 1);
		if (!ptr->is_free)
		{
			write(1, "\n", 1);
			put_addr(ptr + 1);
			ft_putstr(" - ");
			put_addr(((void*)(ptr + 1) + (size_t)ptr->size));
			ft_putstr(" : ");
			ft_putnbr(ptr->size);
			ft_putstr(" octets\n");
		//	print_memory(ptr, sizeof(t__malloc_block__) + ptr->size);
			*total += sizeof(t__malloc_block__) + ptr->size;
		}
		ptr = ptr->next;
	}
}

void	show_alloc_mem()
{
	extern struct s__malloc_instance__	g__malloc_instance__;
	int									total;
	int									i;
	char								*strings[3] = {"TINY : ", "SMALL : ", "LARGE : "};

	ft_putstr("------------- SHOW_ALLOC_MEM() -------------\n\n");
	total = 0;
	i = 0;
	while (i <= __MALLOC_LARGE__)
	{
		if (g__malloc_instance__.zone[i])
		{
			ft_putstr(strings[i]);
			if (i != __MALLOC_LARGE__)
				put_addr(g__malloc_instance__.zone_addr[i]);
			else
				put_addr(g__malloc_instance__.zone[i]);
			print_zone(g__malloc_instance__.zone[i],
				&total);
		}
		i++;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putendl(" octets");
}

/*
 * *	SHOW_ALLOC_MEM_EX()
 * *		-	PID
 * *		-	TID
 * *		-	LostFragments
 * *		-	print_memory()
 */
