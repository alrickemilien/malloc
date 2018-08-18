/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 13:11:01 by aemilien          #+#    #+#             */
/*   Updated: 2018/08/18 14:08:30 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t__malloc_instance__		g__malloc_instance__ = {0,
	{
		{
			0,
			0
		},
		{
			0,
			0,
			0
		},
		{
			0,
			0,
			0,
			0,
			0,
			0
		},
		0
	},
	{
		0,
		0,
		0
	},
	{
		0,
		0,
		0
	},
};

struct s__malloc_thread_safe__	g__malloc_thread_safe__ = {
	PTHREAD_MUTEX_INITIALIZER,
	{
		PTHREAD_MUTEX_INITIALIZER,
		PTHREAD_MUTEX_INITIALIZER,
		PTHREAD_MUTEX_INITIALIZER
	}
};

/*
** This function wraps the mmap function by creating a new zone
** @param
** size_t size : size de l'allocation avec mmap
*/

void							*new_zone(size_t size)
{
	t__malloc_block__	*ptr;

	if ((ptr = mmap(0,
				size + sizeof(t__malloc_block__),
				PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE,
				-1, 0)) == MAP_FAILED)
		return (NULL);
	ptr->size = size;
	ptr->is_free = 1;
	return ((void*)ptr);
}

/*
** This function initializes an extern char** environ array
** that will be used later in the code to handle
** malloc's features
*/

void							init_malloc_env(void)
{
	extern char	**environ;
	char		*malloc_env_vars[6];
	int			i;
	int			j;

	malloc_env_vars[MALLOCSCRIBBLE] = "MallocScribble";
	malloc_env_vars[MALLOCPRESCRIBBLE] = "MallocPreScribble";
	malloc_env_vars[MALLOCGUARDEDGES] = "MallocGuardEdges";
	malloc_env_vars[MALLOCDONOTPROTECTPRELUDE] = "MallocDoNotProtectPrelude";
	malloc_env_vars[MALLOCDONOTPROTECTPOSTLUDE] = "MallocDoNotProtectPostlude";
	malloc_env_vars[MALLOCDONOTPROTECTPOSTLUDE + 1] = 0;
	j = 0;
	while (environ[j])
	{
		i = 0;
		while (malloc_env_vars[i])
		{
			if (ft_strstr(environ[j], malloc_env_vars[i]) == environ[j])
				g__malloc_instance__.options.malloc_env_vars[i] = 1;
			i++;
		}
		j++;
	}
}

/*
** Append page_size to zone size until it reaches __MALLOC_X_ZONE_SIZE__
** with X corresponding to a zone
** The options.zone_size[__MALLOC_LARGE__] is set to 0 at start,
** but will evolve during the programm by allocations and frees
*/

void							init(void)
{
	int page_size;

	LOCK(&g__malloc_thread_safe__.global);
	init_malloc_env();
	page_size = getpagesize();
	g__malloc_instance__.options.absolute_max_size = SIZE_MAX - (2 * page_size);
	g__malloc_instance__.options.zone_size[__MALLOC_TINY__] = 0;
	g__malloc_instance__.options.zone_size[__MALLOC_SMALL__] = 0;
	while (g__malloc_instance__.options.zone_size[__MALLOC_TINY__]
			< __MALLOC_TINY_ZONE_SIZE__)
		g__malloc_instance__.options.zone_size[__MALLOC_TINY__] += page_size;
	while (g__malloc_instance__.options.zone_size[__MALLOC_SMALL__]
			< __MALLOC_SMALL_ZONE_SIZE__)
		g__malloc_instance__.options.zone_size[__MALLOC_SMALL__] += page_size;
	g__malloc_instance__.is_init = 1;
	g__malloc_instance__.options.zone_quantums[__MALLOC_TINY__] =
		__MALLOC_TINY_QUANTUM__;
	g__malloc_instance__.options.zone_quantums[__MALLOC_SMALL__] =
		__MALLOC_SMALL_QUANTUM__;
	g__malloc_instance__.options.zone_quantums[__MALLOC_LARGE__] =
		getpagesize();
	UNLOCK(&g__malloc_thread_safe__.global);
}

/*
** This function initiaize the structure that identify the zone
*/

int								init_zone(int macro)
{
	if (macro == __MALLOC_LARGE__)
		return (1);
	LOCK(&g__malloc_thread_safe__.zone[macro]);
	if (!(g__malloc_instance__.zone[macro] =
			new_zone(g__malloc_instance__.options.zone_size[macro])))
	{
		UNLOCK(&g__malloc_thread_safe__.zone[macro]);
		return (0);
	}
	g__malloc_instance__.zone[macro]->is_free = 1;
	g__malloc_instance__.zone[macro]->size =
		g__malloc_instance__.options.zone_size[macro];
	g__malloc_instance__.zone_addr[macro] = g__malloc_instance__.zone[macro];
	UNLOCK(&g__malloc_thread_safe__.zone[macro]);
	return (1);
}

size_t							get_size_according_to_quantum_zone(
		size_t size,
		int zone)
{
	size_t	quantum;
	size_t	ret;

	quantum = g__malloc_instance__.options.zone_quantums[zone];
	ret = 0;
	while (ret < size)
		ret += quantum;
	return (ret);
}
