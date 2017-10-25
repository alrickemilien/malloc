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

static void		*alloc_large(size_t size, int *malloc_env_vars)
{
	t__malloc_block__	*new_block;
	void				*p;

	p = NULL;
	if (malloc_env_vars[MallocGuardEdges]
			|| malloc_env_vars[MallocDoNotProtectPostlude])
	{
		if (( p = mmap(0, getpagesize(), PROT_NONE,
						MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED )
			return (NULL);
	}
	if (!(new_block = mmap(p, size + sizeof(t__malloc_block__),
					PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	if (malloc_env_vars[MallocGuardEdges]
			|| malloc_env_vars[MallocDoNotProtectPrelude])
	{
		if ((mmap(new_block + size + sizeof(t__malloc_block__), getpagesize(), PROT_NONE,
						MAP_ANON | MAP_PRIVATE | MAP_FIXED, -1, 0)) == MAP_FAILED)
			return (NULL);
	}
	return (new_block);	
}

// Dans la boucle il faut detecter les LostSegment made by realloc (BONUS)
static void
*new_block(
		struct s__malloc_instance__	*g__malloc_instance__,
		t__malloc_block__			**block,
		size_t						size)
{
	t__malloc_block__	*new_block;
	t__malloc_block__	*tmp;
	int					tid;

	tid = (int)pthread_self();
	if (size > __MALLOC_SMALL_LIMIT__)
	{
		if (!(new_block = alloc_large(size, g__malloc_instance__->options.malloc_env_vars)))
			return (NULL);
	}
	else
	{
		new_block = (void*)(*block + 1) + (*block)->size;
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
	}
	new_block->size = size;
	new_block->is_free = 0;
	new_block->next = *block;
	*block = new_block;
	return (new_block + 1);
}

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

void	*malloc(size_t size)
{
	extern char								**environ;
	extern struct s__malloc_instance__		g__malloc_instance__;
	extern struct s__malloc_thread_safe__	g__malloc_thread_safe__;
	void									*ret;
	int										macro;
	//	struct rlimit 						rlim;

	//	if (getrlimit(RLIMIT_DATA, &rlim) < 0)
	//		return (NULL);
	//	put_addr(((void*)((size_t)rlim.rlim_cur)));
	ret = NULL;
	if (!g__malloc_instance__.is_init)
		init();
	macro = get_zone(size);
	if (!g__malloc_instance__.zone[macro])
		if (!init_zone(macro))
			return (NULL);
	LOCK( &g__malloc_thread_safe__.zone[macro] );
	if( !(ret = new_block(&g__malloc_instance__, &g__malloc_instance__.zone[macro], size)))
	{
		UNLOCK ( &g__malloc_thread_safe__.zone[macro] );
		return (NULL);
	}
	if (g__malloc_instance__.options.malloc_env_vars[MallocPreScribble])
		ft_memset(ret, 0xAA, ((t__malloc_block__*)ret - 1)->size);
	UNLOCK( &g__malloc_thread_safe__.zone[macro] );
	//	ft_putnbr(size);
	//	write(1, "\n", 1);
	//	((char*)ret)[0] = '*';
	//	show_alloc_mem();
	return (ret);
}
