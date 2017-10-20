/*
 *		ATTENTION!
 *		Les variables globales depndent d'un processus.
 *		Lors d'un fork, celle ci est duplique et n'est plus partagee
 *		meme si c'est un pointeur
 */

#include "malloc.h"

static inline int get_zone(size_t size)
{
	if (size < __MALLOC_TINY_LIMIT__)
		return (__MALLOC_TINY__);
	if (size < __MALLOC_SMALL_LIMIT__)
		return (__MALLOC_SMALL__);
	return (__MALLOC_LARGE__);
}

// Dans la boucle il faut detecter les LostSegment made by realloc (BONUS)
static void
*new_block(
			t__malloc_block__	**block,
			size_t				size)
{
	t__malloc_block__	*new_block;
	t__malloc_block__	*tmp;
	int					tid;

	tid = (int)pthread_self();
	tmp = *block;
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
	if (size > __MALLOC_SMALL_LIMIT__)
		new_block = mmap(0,
			size + sizeof(t__malloc_block__),
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	else
		new_block = (void*)(*block + 1) + (*block)->size;
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
	int										macro;
	//struct rlimit 						rlim;

	ret = NULL;
	if (!g__malloc_instance__.is_init)
		init();
	macro = get_zone(size);
	if (!g__malloc_instance__.zone[macro])
		if (!init_zone(macro))
			return (NULL);
	LOCK( &g__malloc_thread_safe__.zone[macro] );
	ret = new_block(&g__malloc_instance__.zone[macro], size);
	UNLOCK( &g__malloc_thread_safe__.zone[macro] );
	ft_putnbr(size);
	write(1, "\n", 1);
	((char*)ret)[0] = '*';
	show_alloc_mem();
	return (ret);
}
