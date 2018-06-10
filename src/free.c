#include "malloc.h"

/*
*	* This function identfys the zone bi its size, returnng an int corresponding to the zone between :
* * __MALLOC_TINY_LIMIT__ - __MALLOC_SMALL__ - __MALLOC_SMALL_LIMIT__
*/
static inline int get_zone(size_t size)
{
	if (size < __MALLOC_TINY_LIMIT__)
		return (__MALLOC_TINY__);
	if (size < __MALLOC_SMALL_LIMIT__)
		return (__MALLOC_SMALL__);
	return (__MALLOC_LARGE__);
}

/*
* * @params
* * 	t__malloc_block__ *ptr : the ptr to check
* *		t__malloc_block__	*tmp : the instance of allocation of the programme
* *
* * Check if the ptr passed as parameter
* *
* * - Check if the ptr is in the range of the zone by checking the values of the addr
* * We could check this case for example and validate it
* * ex : instance->zone_addr[__MALLOC_TINY__] . . . . ptr . . . . . . . . instance->zone_addr[__MALLOC_SMALL__] . . . . etc
* *                                            __MALLOC_TINY_ZONE_SIZE__
* *
* * - Loop over each block of the zone,
* * a block is cut in block that start with a size and a ptr to the next block
* *
* *    																				< next ---------------------------------------------------------
* * instance->zone_addr[__MALLOC_TINY__] . . . . . . [size, ptr] . . . . . . . . [size, ptr] . . . . . . [size, ptr] . . instance->zone_addr[__MALLOC_SMALL__]
* *
*/
// static int	is_ptr_valid(
// 		t__malloc_block__ *ptr,
// 		struct s__malloc_instance__ *instance)
// {
// 	t__malloc_block__	*block;
// 	t__malloc_block__	*tmp;
// 	size_t					m;
//
// 	block = ptr;
//
// 	if ( !((size_t)block >= (size_t)instance->zone_addr[__MALLOC_TINY__]
// 				&& (size_t)block < ((size_t)instance->zone_addr[__MALLOC_TINY__]
// 					+ __MALLOC_TINY_ZONE_SIZE__))
// 			&& !(((size_t)block >= (size_t)instance->zone_addr[__MALLOC_SMALL__]
// 					&& (size_t)block < ((size_t)instance->zone_addr[__MALLOC_SMALL__]
// 						+ __MALLOC_SMALL_ZONE_SIZE__))) )
// 		return (0);
//
// 	m = __MALLOC_TINY__;
//
// 	while (m <= __MALLOC_LARGE__)
// 	{
// 		tmp = instance->zone[m];
// 		while (tmp)
// 		{
// 			if (tmp == block)
// 				return (1);
//
// 			tmp = tmp->next;
// 		}
//
// 		m++;
// 	}
//
// 	return (0);
// }

/*
* * Allocates the memory in special case zhen the size to alloc is a LARGE allocation
* * In this case, the mmap allocated memory represents a new block itself of the LARGE allocation
* *
* * - When the zone[__MALLOC_LARGE__] correspond to the block passed as parameter
* *
*/
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

/*
* * New call of the free function
* *
* * - Handle the case when *ptr == NULL
* * - Get the zone where the ptr is
* * - Lock the data
* * - Set the block as freed with its flag
* * - ? When MallocScribble is set, fill the data zih 0x55 before freeing it
* * - ? When the block is a big block from __MALLOC_LARGE_ZONE__ , unmap it directly
*/
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

	//	show_alloc_mem();


	if (!ptr) {
		ft_putstr("\nje quitte free\n");
		return;
	}

	block = (t__malloc_block__*)ptr - 1;


	/*
	 *		POUR LES TEST DES FUNCTIONS DE LIB_C
	 */
	// if (!is_ptr_valid(block, &g__malloc_instance__)) {
	// 	ft_putstr("\nje quitte free car le pointeur n'est pas valide\n");
	// 	return;
	// }

	ft_putstr("Le pointeur a pour taille ");
	ft_putnbr(block->size);
	ft_putstr("\n");

	macro = get_zone(block->size);

	LOCK( &g__malloc_thread_safe__.zone[macro] );

	block->is_free = 1;

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
