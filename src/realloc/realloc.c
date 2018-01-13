#include "malloc.h"

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

	ft_putstr("ici\n");
	put_addr(after);
	ft_putstr("\n");
	put_addr(tmp);
	ft_putstr("\n");

	ft_putstr("2\n");

	//if ( ((size_t)ptr - (size_t)after) < size - ptr->size)
	if( (size_t)tmp > (size_t)ptr + size + sizeof(t__malloc_block__) )
		return (1);

	ft_putstr("3\n");

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
	ft_putstr("On me passe le pointeur ");
	put_addr(ptr);
	ft_putstr("\n");
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
