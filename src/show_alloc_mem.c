#include "malloc.h"

static	void	ft_putnbr_hex(size_t n)
{
	char str[16] = "0123456789ABCDEF";

	ft_putstr("0x");
	if (!n)
	{
		write(1, "0", 1);
		return ;
	}
	while (n)
	{
		write(1, &str[n % 16], 1);
		n >>= 4;
	}
}

void	show_alloc_mem()
{
	extern struct s__malloc_instance__	g__malloc_instance__;
	t__malloc_block__					*ptr;

	ptr = g__malloc_instance__.tiny_zone;
	/*while (ptr)
	  {
	  ft_putstr("----- BLOCK ----\n");
	  ft_putstr("size : ");
	  ft_putnbr(ptr->size);
	  write(1, "\n", 1);
	  print_memory(ptr + 1, ptr->size);
	  ptr = ptr->next;
	  }*/
	ft_putstr("TINY : ");
	ft_putnbr_hex((size_t)g__malloc_instance__.tiny_zone_addr.addr);
	ft_putnbr_hex(sizeof(t__malloc_block__));
	while (ptr)
	{
		write(1, "\n", 1);
		if (!ptr->is_free)
		{
			print_memory(ptr, sizeof(ptr) + ptr->size);
			write(1, "\n", 1);
			ft_putnbr_hex((size_t)(ptr + 1));
			ft_putstr(" - ");
			ft_putnbr_hex((size_t)(ptr + 1) + (size_t)ptr->size);
			write(1, "\n", 1);
		}
		ptr = ptr->next;
	}
}
