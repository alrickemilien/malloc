#include "malloc.h"

void	show_alloc_mem()
{
	extern struct s__malloc_instance__ g__malloc_instance__;
	t__malloc_block__					*ptr;

	ptr = g__malloc_instance__.block;
	while (ptr)
	{
		ft_putstr("----- BLOCK ----\n");
		ft_putstr("size : ");
		ft_putnbr(ptr->size);
		write(1, "\n", 1);
		print_memory(ptr, sizeof(ptr->size));
		ptr = ptr->next;
	}

}
