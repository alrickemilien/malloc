#include "malloc.h"

// For realloc(), the input pointer is still valid if reallocation failed.

static int	is_ptr_valid(
		t__malloc_block__ *ptr,
		struct s__malloc_instance__ *instance)
{
	t__malloc_block__	*block;
	t__malloc_block__	*tmp;

	block = ptr - 1;
	if ( ((size_t)block >= (size_t)instance->tiny_zone_addr
				&& (size_t)block < ((size_t)instance->tiny_zone_addr +__MALLOC_TINY_ZONE_SIZE__))
		|| (((size_t)block >= (size_t)instance->small_zone_addr
				&& (size_t)block < ((size_t)instance->small_zone_addr +__MALLOC_SMALL_ZONE_SIZE__))) )
		return (1);
	tmp = instance->large_zone;
	while (tmp)
	{
		if (tmp == block)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	*realloc(void *ptr, size_t size)
{
	extern struct s__malloc_instance__		g__malloc_instance__;

	if (!ptr)
		return (malloc(size));
	if (!size)
		free(ptr);
	if (!is_ptr_valid(ptr, &g__malloc_instance__))
		return (NULL);
	return (ptr);
}
