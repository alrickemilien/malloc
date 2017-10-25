#include "malloc.h"

/*static void put_addr(void *param)
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
  }*/

static inline int get_zone(size_t size)
{
	if (size < __MALLOC_TINY_LIMIT__)
		return (__MALLOC_TINY__);
	if (size < __MALLOC_SMALL_LIMIT__)
		return (__MALLOC_SMALL__);
	return (__MALLOC_LARGE__);
}

static int	is_ptr_valid(
		t__malloc_block__ *ptr,
		struct s__malloc_instance__ *instance)
{
	t__malloc_block__	*block;
	t__malloc_block__	*tmp;

	block = ptr;
	if ( ((size_t)block >= (size_t)instance->zone_addr[__MALLOC_TINY__]
				&& (size_t)block < ((size_t)instance->zone_addr[__MALLOC_TINY__]
					+ __MALLOC_TINY_ZONE_SIZE__))
			|| (((size_t)block >= (size_t)instance->zone_addr[__MALLOC_SMALL__]
					&& (size_t)block < ((size_t)instance->zone_addr[__MALLOC_SMALL__]
						+ __MALLOC_SMALL_ZONE_SIZE__))) )
		return (1);
	tmp = instance->zone[__MALLOC_LARGE__];
	while (tmp)
	{
		if (tmp == block)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void
unmap_large(
		struct s__malloc_instance__ *g__malloc_instance__,
		t__malloc_block__			*block)
{
	t__malloc_block__						*tmp;

	tmp = g__malloc_instance__->zone[__MALLOC_LARGE__];
	if (block == g__malloc_instance__->zone[__MALLOC_LARGE__])
		g__malloc_instance__->zone[__MALLOC_LARGE__] = block->next;
	else
	{
		while (tmp && tmp->next != block)
			tmp = tmp->next;
		tmp->next = block->next;
	}
	munmap(block,
			(size_t)block->size + sizeof(t__malloc_block__));
}

void	free(void *ptr)
{
	t__malloc_block__						*block;
	extern struct s__malloc_instance__		g__malloc_instance__;
	extern struct s__malloc_thread_safe__	g__malloc_thread_safe__;
	int										macro;

	if (!ptr)
		return;
	block = (t__malloc_block__*)ptr - 1;
	//	ft_putendl("FREE CALLED");
	/*
	 *		POUR LES TEST DES FUNCTIONS DE LIB_C
	 */
	if (!is_ptr_valid(block, &g__malloc_instance__))
		return ;
	macro = get_zone(block->size);
	LOCK( &g__malloc_thread_safe__.zone[macro] );
	//	put_addr(ptr);
	//	write(1, "\n", 1);
	block->is_free = 1;
	if (g__malloc_instance__.options.malloc_env_vars[MallocScribble])
		ft_memset(ptr, 0x55, (size_t)block->size);
	if (block->size > __MALLOC_SMALL_LIMIT__)
		unmap_large( &g__malloc_instance__, block );
	UNLOCK( &g__malloc_thread_safe__.zone[macro] );
	return ;
}
