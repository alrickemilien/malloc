#include "malloc.h"

static int	is_ptr_valid(
		t__malloc_block__ *ptr,
		struct s__malloc_instance__ *instance)
{
	t__malloc_block__	*block;
	t__malloc_block__	*tmp;
	int					m;

	block = ptr - 1;

	m = __MALLOC_TINY__;
	while (m <= __MALLOC_LARGE__)
	{
		tmp = instance->zone[m];

		while (tmp)
		{
			if (tmp == block)
				return (1);

			tmp = tmp->next;
		}

		m++;
	}

	return (0);
}
static inline int get_zone(size_t size)
{
	if (size < __MALLOC_TINY_LIMIT__)
		return (__MALLOC_TINY__);
	if (size < __MALLOC_SMALL_LIMIT__)
		return (__MALLOC_SMALL__);
	return (__MALLOC_LARGE__);
}

	static int
can_extend(
		struct s__malloc_instance__	*instance,
		t__malloc_block__			*ptr,
		size_t						size,
		int							current_zone)
{
	void				*after;
	t__malloc_block__        *tmp;

	if (current_zone == __MALLOC_LARGE__)
		return (0);

	after = (void*) ((size_t)ptr + ptr->size + sizeof(t__malloc_block__));

	// Check if the new adress is not over the stack
	if ((size_t)after > (size_t) instance->zone[current_zone]
			+ instance->options.zone_size[current_zone])
		return (0);

	// Get the top of the stack in tmp
	tmp = instance->zone[current_zone];

	// In this case, ptr is the top of the stack so it can extend easy
	if (tmp == ptr)
		return (1);

	// Get the adress of the block right after ptr
	while (tmp && tmp->next != ptr)
		tmp = tmp->next;

	if( (size_t)tmp > (size_t)ptr + size + sizeof(t__malloc_block__) )
		return (1);

	return (0);
}

void		*process_realloc(void *ptr, size_t size)
{
	void	*ret;
	size_t	i;

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

void	*realloc(void *ptr, size_t size)
{
	extern struct s__malloc_instance__		g__malloc_instance__;
	extern struct s__malloc_thread_safe__   g__malloc_thread_safe__;
	int										current_zone;
	int										new_zone;

	if (!ptr)
		return malloc(size);

	if (!size) {
		free(ptr);
	}

	if (!is_ptr_valid(ptr, &g__malloc_instance__)) {
		return (NULL);
	}

	new_zone = get_zone(size);
	current_zone = get_zone(((t__malloc_block__*)ptr - 1)->size);
	if (current_zone != new_zone)
	{
		return process_realloc(ptr, size);
	}
	else /* Stay on the same zone */
	{
		if (size <= ((t__malloc_block__*)ptr - 1)->size)
		{
			LOCK( &g__malloc_thread_safe__.zone[current_zone] );
			((t__malloc_block__*)ptr - 1)->size = size;
			UNLOCK( &g__malloc_thread_safe__.zone[current_zone] );
		}
		else
		{
			/* check si il y a un LostFragment entre le current et le prochain block*/
			if (can_extend(&g__malloc_instance__,
						((t__malloc_block__*)ptr - 1),
						size,
						current_zone))
			{
				LOCK( &g__malloc_thread_safe__.zone[current_zone] );
				((t__malloc_block__*)ptr - 1)->size = size;
				UNLOCK( &g__malloc_thread_safe__.zone[current_zone] );
			}
			else {
				return process_realloc(ptr, size);
			}
		}
	}

	return (ptr);
}
