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

static int get_zone(size_t size)
{
	if (size < __MALLOC_TINY_LIMIT__)
		return (__MALLOC_TINY__);
	if (size < __MALLOC_SMALL_LIMIT__)
		return (__MALLOC_SMALL__);
	return (__MALLOC_LARGE__);
}

/*static void *get_zone_ptr(
		int							zone,
		struct s__malloc_instance__ *instance)
{
	if ( zone == __MALLOC_TINY__ )
		return (instance->tiny_zone);
	if ( zone == __MALLOC_SMALL__ )
		return (instance->small_zone);
	return (instance->large_zone);
}*/

void	*realloc(void *ptr, size_t size)
{
	extern struct s__malloc_instance__		g__malloc_instance__;
	int										new_zone;
	int										current_zone;
	void									*ret;
	size_t									i;

	if (!ptr)
		return (malloc(size));
	if (!size)
		free(ptr);
	if (!is_ptr_valid(ptr, &g__malloc_instance__))
		return (NULL);

	new_zone = get_zone(size);
	current_zone = get_zone(((t__malloc_block__*)ptr - 1)->size);
	if (current_zone != new_zone)
		return (ptr);
	else /* Stay on the same zone */
	{
		if (size <= ((t__malloc_block__*)ptr - 1)->size)
			((t__malloc_block__*)ptr - 1)->size = size;
		else
		{
			/* check si il y a un LostFragment entre le current et le prochain block*/
			//if (can_extend(((t__malloc_block__*)ptr - 1), size))
			//	((t__malloc_block__*)ptr - 1)->size = size;
			//else
			if(!(ret = malloc(size)))
				return (NULL);
			i = 0;
			while (i < ((t__malloc_block__*)ptr - 1)->size)
			{
				((char*)ret)[i] = ((char*)ptr)[i];
				i++;
			}
			free(ptr); /* free l'ancien maillon */
			return (ret);
		}
	}
	return (ptr);
}
