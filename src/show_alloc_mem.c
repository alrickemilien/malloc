/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 13:35:33 by aemilien          #+#    #+#             */
/*   Updated: 2018/08/18 13:53:42 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		print_zone(t__malloc_block__ *ptr, int *total)
{
	while (ptr)
	{
		if (!ptr->is_free)
		{
			put_addr(ptr + 1);
			ft_putstr(" - ");
			put_addr(((void*)(ptr + 1) + (size_t)ptr->size));
			ft_putstr(" : ");
			ft_putnbr(ptr->size);
			ft_putstr(" octets\n");
			*total += sizeof(t__malloc_block__) + ptr->size;
		}
		ptr = ptr->next;
	}
}

static void		print_zone_name(int i)
{
	if (i == __MALLOC_LARGE__)
		ft_putstr("LARGE : ");
	else if (i == __MALLOC_SMALL__)
		ft_putstr("SMALL : ");
	else if (i == __MALLOC_TINY__)
		ft_putstr("TINY : ");
}

void			show_alloc_mem(void)
{
	extern t__malloc_instance__	g__malloc_instance__;
	int							total;
	int							i;

	ft_putstr("------------- SHOW_ALLOC_MEM() -------------\n");
	total = 0;
	i = 0;
	while (i <= __MALLOC_LARGE__)
	{
		if (g__malloc_instance__.zone[i])
		{
			print_zone_name(i);
			if (i != __MALLOC_LARGE__)
				put_addr(g__malloc_instance__.zone_addr[i]);
			else
				put_addr(g__malloc_instance__.zone[i]);
			write(1, "\n", 1);
			print_zone(g__malloc_instance__.zone[i],
				&total);
		}
		i++;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putendl(" octets");
}

/*
**	@TODO SHOW_ALLOC_MEM_EX()
**		-	PID
**		-	TID
**		-	LostFragments
**		-	print_memory()
*/

void			show_alloc_mem_ex(void)
{
	extern t__malloc_instance__	g__malloc_instance__;
	int							total;
	int							i;

	ft_putstr("------------- SHOW_ALLOC_MEM() -------------\n");
	total = 0;
	i = 0;
	while (i <= __MALLOC_LARGE__)
	{
		if (g__malloc_instance__.zone[i])
		{
			print_zone_name(i);
			if (i != __MALLOC_LARGE__)
				put_addr(g__malloc_instance__.zone_addr[i]);
			else
				put_addr(g__malloc_instance__.zone[i]);
			write(1, "\n", 1);
			print_zone(g__malloc_instance__.zone[i],
				&total);
		}
		i++;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putendl(" octets");
}
