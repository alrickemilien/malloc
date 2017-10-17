#include "malloc.h"

void	free(void *ptr)
{
	if (!ptr) {
		return;
	}
	((t__malloc_block__*)ptr)->is_free = 0;
	return ;
}
