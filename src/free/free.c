#include "malloc.h"

void	free(void *ptr)
{
	if (!ptr) {
		return;
	}
	((t__malloc_block__*)ptr - 1)->is_free = 1;
	return ;
}
