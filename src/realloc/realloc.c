#include "malloc.h"

static int	is_ptr_valid(
		t__malloc_block__ *ptr,
		struct s__malloc_instance__ *instance)
{
	t__malloc_block__	*block;
	t__malloc_block__	*tmp;
	int					m;

	block = ptr - 1;
	if ( !((size_t)block >= (size_t)instance->zone_addr[__MALLOC_TINY__]
				&& (size_t)block < ((size_t)instance->zone_addr[__MALLOC_TINY__]
					+ __MALLOC_TINY_ZONE_SIZE__))
			&& !(((size_t)block >= (size_t)instance->zone_addr[__MALLOC_SMALL__]
					&& (size_t)block < ((size_t)instance->zone_addr[__MALLOC_SMALL__]
						+ __MALLOC_SMALL_ZONE_SIZE__))) )
		return (0);

	ft_putstr("bonjour monsiur\n");

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

	if (current_zone == __MALLOC_LARGE__)
		return (0);

		ft_putstr("in can extend\n");
		ft_putnbr(ptr->size);
		ft_putstr("\n");
		ft_putnbr(size);
		ft_putstr("\n");
		put_addr(ptr);
		ft_putstr("\n");
	after = (void*) ((size_t)ptr + ptr->size + sizeof(t__malloc_block__));
	put_addr(after);
	ft_putstr("\n");

	if ((size_t)after > (size_t) instance->zone[current_zone]
			+ instance->options.zone_size[current_zone])
		return (0);

	if (is_ptr_valid(ptr, instance))
		return (0);

		ft_putstr("je suis n rut\n");


	if ( ((size_t)after - (size_t)ptr) < size - ptr->size)
		return (1);

		ft_putstr("je suis un jambon");

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
	extern void *lastAllocMem;

	ft_putstr("\nje suis ici dans realloc\n");
	if (!ptr)
	{
		lastAllocMem = malloc(size);
		ft_putstr("Realloc return le pointeur car le pointeur donne en parametre est null");
		put_addr(lastAllocMem);
		ft_putstr("\n");
		return lastAllocMem;
	}

	if (!size) {
		ft_putstr("je free ptr dans realloc\n");
		ft_putstr("on me demande de free le pointeur ");
		put_addr(ptr);
		ft_putstr("\n");
		free(ptr);
	}

	if (!is_ptr_valid(ptr, &g__malloc_instance__))
		return (NULL);

	new_zone = get_zone(size);
	current_zone = get_zone(((t__malloc_block__*)ptr - 1)->size);
	if (current_zone != new_zone)
	{
		lastAllocMem = process_realloc(ptr, size);
		ft_putstr("Realloc return le pointeur ");
		put_addr(lastAllocMem);
		ft_putstr("\n");
		return lastAllocMem;
	}
	else /* Stay on the same zone */
	{
		if (size <= ((t__malloc_block__*)ptr - 1)->size)
		{
			LOCK( &g__malloc_thread_safe__.zone[current_zone] );
			ft_putstr("je renvois le meme pointeur je modifie juste la size car la size est plus petite que actuelle\n");
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
				ft_putstr("je renvois le meme pointeur je modifie juste la size car je peux extend my size, ma nouvelle size est ");
				ft_putnbr(size);
				ft_putstr("\n");
				((t__malloc_block__*)ptr - 1)->size = size;
				UNLOCK( &g__malloc_thread_safe__.zone[current_zone] );
			}
			else {
				ft_putstr("follow\n");
				lastAllocMem = process_realloc(ptr, size);
				ft_putstr("Realloc return le pointeur ");
				put_addr(lastAllocMem);
				ft_putstr("\n");
				ft_putstr("je quitte realloc\n");
				return lastAllocMem;
			}
		}
	}

	lastAllocMem = ptr;

	ft_putstr("Realloc return le pointeur ");
	put_addr(ptr);
	ft_putstr("\n");
	ft_putstr("je quitte realloc\n");

	return (ptr);
}
