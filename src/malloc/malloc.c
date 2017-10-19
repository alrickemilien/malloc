/*
 *		ATTENTION!
 *		Les variables globales depndent d'un processus.
 *		Lors d'un fork, celle ci est duplique et n'est plus partagee
 *		meme si c'est un pointeur
 */

#include "malloc.h"

void	*new_block(t__malloc_block__ **block, size_t size)
{
	t__malloc_block__	*new_block;
	t__malloc_block__	*tmp;
	size_t				length;
	int					tid;

	tid = (int)pthread_self();
	tmp = *block;
	length = 0;
	while (tmp)
	{
		if (tmp->is_free && size <= tmp->size)
		{
			tmp->size = size;
			tmp->is_free = 0;
			new_block = tmp;
			return (new_block + 1);
		}
		length += tmp->size + sizeof(t__malloc_block__);
		tmp = tmp->next;
	}
	new_block = ((void*)(*block)) + length;
	new_block->size = size;
	new_block->is_free = 0;
	new_block->next = *block;
	*block = new_block;
	return (new_block + 1);
}


void	*malloc(size_t size)
{
	extern char								**environ;
	extern struct s__malloc_instance__		g__malloc_instance__;
	extern struct s__malloc_thread_safe__	g__malloc_thread_safe__;
	void									*ret;

	if (!g__malloc_instance__.is_init)
		init();
	if (!g__malloc_instance__.tiny_zone)
		init_tiny_zone();
	if (size < __MALLOC_TINY_LIMIT__)
	{
		LOCK( &g__malloc_thread_safe__.tiny );
		ret = new_block(&g__malloc_instance__.tiny_zone, size);
		UNLOCK( &g__malloc_thread_safe__.tiny );
		return (ret);
	}
	return (NULL);
}
