/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 11:50:48 by aemilien          #+#    #+#             */
/*   Updated: 2018/08/18 14:41:00 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**  This functon allocates for the special case of large allocations
** - When the MallocGuardEdges flag is set,
** set the PROT_NONE flag to allocate memory,
** meaning that pages may not be accessed,
** and create a pagezise blok at start of the fat block
** - Allocated the fat block
** - When the MallocGuardEdges flag is set,
** set the PROT_NONE flag to allocate memory,
** meaning that pages may not be accessed,
** and create a pagezise blok at end of the fat block
*/

static void		*alloc_large(size_t size, int *malloc_env_vars)
{
	t__malloc_block__	*new_block;
	void				*p;

	p = NULL;
	if (malloc_env_vars[MALLOCGUARDEDGES]
			&& !malloc_env_vars[MALLOCDONOTPROTECTPOSTLUDE])
	{
		if ((p = mmap(0, getpagesize(), PROT_NONE,
						MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
			return (NULL);
	}
	if (!(new_block = mmap(p, size + sizeof(t__malloc_block__),
					PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	if (malloc_env_vars[MALLOCGUARDEDGES]
			&& !malloc_env_vars[MALLOCDONOTPROTECTPRELUDE])
	{
		if ((mmap(new_block + size + sizeof(t__malloc_block__),
						getpagesize(), PROT_NONE,
						MAP_ANON | MAP_PRIVATE | MAP_FIXED,
						-1, 0)) == MAP_FAILED)
			return (NULL);
	}
	return (new_block);
}

static void		*search_freed_block(
			t__malloc_block__ **block,
			size_t size)
{
	t__malloc_block__		*tmp;

	tmp = *block;
	while (tmp)
	{
		if (tmp->is_free && size <= tmp->size)
		{
			tmp->size = size;
			tmp->is_free = 0;
			return (tmp + 1);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static void		*new_block(
					t__malloc_instance__ *g__malloc_instance__,
					t__malloc_block__ **block,
					size_t size)
{
	t__malloc_block__		*new_block;
	t__malloc_block__		*tmp;

	if (size > __MALLOC_SMALL_LIMIT__)
	{
		if (!(new_block = alloc_large(size,
						g__malloc_instance__->options.malloc_env_vars)))
			return (NULL);
	}
	else
	{
		new_block = (void*)(*block + 1) + (*block)->size;
		if ((tmp = search_freed_block(block, size)))
			return (tmp);
	}
	new_block->size = size;
	new_block->is_free = 0;
	new_block->next = *block;
	*block = new_block;
	return (new_block + 1);
}

void			*malloc(size_t size)
{
	extern t__malloc_instance__				g__malloc_instance__;
	extern struct s__malloc_thread_safe__	g__malloc_thread_safe__;
	void									*ret;
	int										macro;
	struct rlimit							rlim;

	if (getrlimit(RLIMIT_DATA, &rlim) > 0 && (size_t)rlim.rlim_max < size)
		return (NULL);
	if (!g__malloc_instance__.is_init)
		init();
	macro = get_zone(size);
	if (!g__malloc_instance__.zone[macro] && !init_zone(macro))
		return (NULL);
	LOCK(&g__malloc_thread_safe__.zone[macro]);
	if (!(ret = new_block(&g__malloc_instance__,
					&g__malloc_instance__.zone[macro],
					get_size_according_to_quantum_zone(size, macro))))
	{
		UNLOCK(&g__malloc_thread_safe__.zone[macro]);
		return (NULL);
	}
	if (g__malloc_instance__.options.malloc_env_vars[MALLOCPRESCRIBBLE])
		ft_memset(ret, 0xAA, ((t__malloc_block__*)ret - 1)->size);
	UNLOCK(&g__malloc_thread_safe__.zone[macro]);
	return (ret);
}
