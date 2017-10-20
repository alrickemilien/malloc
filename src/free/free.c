#include "malloc.h"

void	free(void *ptr)
{
	t__malloc_block__		*block;

	if (!ptr)
		return;
	block = (t__malloc_block__*)ptr - 1;
	block->is_free = 1;
	ft_putendl("FREE CALLED");
	if (block->size > __MALLOC_SMALL_LIMIT__)
		munmap(block,
				(size_t)block->size + sizeof(t__malloc_block__));
	return ;
}
