/*
 *		ATTENTION!
 *		Les variables globales depndent d'un processus.
 *		Lors d'un fork, celle ci est duplique et n'est plus partagee
 *		meme si c'est un pointeur
 */

#include "malloc.h"

void	*new_block(t__malloc_block__ *block, size_t size)
{
	t__malloc_block__	*new_block;
	t__malloc_block__	*tmp;
	
	tmp = block;

	while (tmp)
	{
		if (tmp->is_free && size <= tmp->size)
		{
			tmp->size = size;
			tmp->is_free = 0;
			new_block = tmp;
			return (new_block + 1);
		}
		tmp = tmp->next;
	}
	(void)block;
	(void)size;

	return (NULL);
}

void	*malloc(size_t size)
{
	extern char **environ;
	extern struct s__malloc_instance__ g__malloc_instance__;

	init();
	if (!g__malloc_instance__.tiny_zone)
	{
		g__malloc_instance__.tiny_zone = new_zone(g__malloc_instance__.options.tiny_zone_size);
		ft_bzero(g__malloc_instance__.tiny_zone, sizeof(t__malloc_block__));
		g__malloc_instance__.tiny_zone->is_free = 1;
		g__malloc_instance__.tiny_zone->size = g__malloc_instance__.options.tiny_zone_size;
		g__malloc_instance__.tiny_zone_addr.addr = g__malloc_instance__.tiny_zone;
	}
	if (size < __MALLOC_TINY_LIMIT__)
	{
		return (new_block(g__malloc_instance__.tiny_zone, size));
	}
	return (NULL);
}
