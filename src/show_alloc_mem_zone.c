#include "malloc.h"

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

/*
* * Foreach zone, put the adresse of the zone
*/
void	show_alloc_mem_zone(int zone)
{
	extern struct s__malloc_instance__	g__malloc_instance__;
	int									total;
	char								*strings[3] = {"TINY : ", "SMALL : ", "LARGE : "};

	ft_putstr("------------- SHOW_ALLOC_MEM_ZONE() -------------\n\n");

	total = 0;
	if (g__malloc_instance__.zone[zone])
	{
		ft_putstr(strings[zone]);

		if (zone != __MALLOC_LARGE__)
			put_addr(g__malloc_instance__.zone_addr[zone]);
		else
			put_addr(g__malloc_instance__.zone[zone]);

		print_zone(g__malloc_instance__.zone[zone],
			&total);
	}

	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putendl(" octets");
}
