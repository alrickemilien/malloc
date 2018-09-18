/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 12:29:59 by aemilien          #+#    #+#             */
/*   Updated: 2018/08/18 14:10:17 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Check if the ptr passed is valid
*/

static int			is_ptr_valid(
		t__malloc_block__ *ptr,
		t__malloc_instance__ *instance)
{
	t__malloc_block__	*block;
	t__malloc_block__	*tmp;
	int					m;

	block = ptr - 1;
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

static int			can_extend(
		t__malloc_instance__ *instance,
		t__malloc_block__ *ptr,
		size_t size,
		int current_zone)
{
	void					*after;
	t__malloc_block__		*tmp;

	if (current_zone == __MALLOC_LARGE__)
		return (0);

	after = (void*)((size_t)ptr + ptr->size + sizeof(t__malloc_block__));

	if ((size_t)after > (size_t)instance->zone[current_zone]
			+ instance->options.zone_size[current_zone])
		return (0);

	tmp = instance->zone[current_zone];

	if (tmp == ptr)
		return (1);

	while (tmp && tmp->next != ptr)
		tmp = tmp->next;

	if ((size_t)tmp > (size_t)ptr + size + sizeof(t__malloc_block__))
		return (1);

	return (0);
}

void				*process_realloc(void *ptr, size_t size)
{
	void	*ret;
	size_t	i;

	if (!(ret = malloc(size)))
		return (NULL);

	i = 0;
	while (i < ((t__malloc_block__*)ptr - 1)->size)
	{
		((char*)ret)[i] = ((char*)ptr)[i];
		i++;
	}

	free(ptr);

	return (ret);
}

/*
** Changes the size of the block passed as parameter
*/

static void			change_size_of_block(
			void *ptr,
			size_t size,
			int current_zone)
{
	extern struct s__malloc_thread_safe__	g__malloc_thread_safe__;

	LOCK(&g__malloc_thread_safe__.zone[current_zone]);

	((t__malloc_block__*)ptr - 1)->size = size;

	UNLOCK(&g__malloc_thread_safe__.zone[current_zone]);
}

void				*realloc(void *ptr, size_t size)
{
	extern t__malloc_instance__						g__malloc_instance__;
	extern struct s__malloc_thread_safe__	g__malloc_thread_safe__;
	int																		current_zone;
	int																		new_zone;

	if (!ptr)
		return (malloc(size));

	if (!size)
		free(ptr);

	if (size > g__malloc_instance__.options.absolute_max_size)
		return (NULL);

	if (!is_ptr_valid(ptr, &g__malloc_instance__))
		return (NULL);

	new_zone = get_zone(size);
	current_zone = get_zone(((t__malloc_block__*)ptr - 1)->size);

	if (current_zone != new_zone)
		return (process_realloc(ptr, size));

	if (size <= ((t__malloc_block__*)ptr - 1)->size)
	{
		change_size_of_block(ptr, size, current_zone);
		return (ptr);
	}

	if (!can_extend(&g__malloc_instance__, ((t__malloc_block__*)ptr - 1),
					size, current_zone))
		return (process_realloc(ptr, size));

	change_size_of_block(ptr, size, current_zone);

	return (ptr);
}
