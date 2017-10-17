/*
 *		ATTENTION!
 *		Les variables globales depndent d'un processus.
 *		Lors d'un fork, celle ci est duplique et n'est plus partagee
 *		meme si c'est un pinteur
 */

#include "malloc.h"

void	*new_block(size_t size)
{
	t__malloc_block__	*ptr;
	
	ptr = mmap(0, 
		size + sizeof(t__malloc_block__),
		PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE,
		-1, 0);
	ptr->size = size;
	ptr->is_free = 0;
	return ((void*)ptr);
}

void	*malloc(size_t size)
{
	extern char **environ;
	extern struct s__malloc_instance__ g__malloc_instance__;
	(void)size;

	init();
	if (!g__malloc_instance__.tiny_zone)
	{
		g__malloc_instance__.tiny_zone = new_block(g__malloc_instance__.options.tiny_zone_size);
		g__malloc_instance__.tiny_zone->is_free = 1;
	}
	ft_putnbr(sizeof(t__malloc_block__));
/*	if (size < __MALLOC_TINY_LIMIT__)
	{

	}*/
	return (NULL);
}
