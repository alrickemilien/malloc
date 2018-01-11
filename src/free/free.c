#include "malloc.h"

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
	int					m;

	block = ptr;
	if ( !((size_t)block >= (size_t)instance->zone_addr[__MALLOC_TINY__]
				&& (size_t)block < ((size_t)instance->zone_addr[__MALLOC_TINY__]
					+ __MALLOC_TINY_ZONE_SIZE__))
			&& !(((size_t)block >= (size_t)instance->zone_addr[__MALLOC_SMALL__]
					&& (size_t)block < ((size_t)instance->zone_addr[__MALLOC_SMALL__]
						+ __MALLOC_SMALL_ZONE_SIZE__))) )
		return (0);
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


	ft_putstr("\nje suis ici dans free\n");
	ft_putstr("\non me demande de free le pointeur ");
	put_addr(ptr);
	ft_putstr("\n");


	if (!ptr) {
		ft_putstr("\nje quitte free\n");
		return;
	}

	block = (t__malloc_block__*)ptr - 1;

	/*
	 *		POUR LES TEST DES FUNCTIONS DE LIB_C
	 */
	if (!is_ptr_valid(block, &g__malloc_instance__)) {
		ft_putstr("\nje quitte free\n");
		return;
	}

	macro = get_zone(block->size);

	LOCK( &g__malloc_thread_safe__.zone[macro] );

	block->is_free = 1;

	ft_putstr("je suis laaaaaaaaaaaaaaaaaaaaaaaaa\n");
	if (g__malloc_instance__.options.malloc_env_vars[MallocScribble])
		ft_memset(ptr, 0x55, (size_t)(block->size));


	if (block->size > __MALLOC_SMALL_LIMIT__) {
		//	show_alloc_mem();
		unmap_large( &g__malloc_instance__, block );
	}

	UNLOCK( &g__malloc_thread_safe__.zone[macro] );

	ft_putstr("\nje quitte free\n");

	return ;
}
