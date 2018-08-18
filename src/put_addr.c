/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_addr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 13:57:41 by aemilien          #+#    #+#             */
/*   Updated: 2018/08/18 14:07:20 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	print(size_t mask, size_t addr, int i)
{
	const char	*str = "0123456789ABCDEF";

	if (!mask)
	{
		write(1, "0", 1);
		return ;
	}
	write(1, "0x", 2);
	while (mask)
	{
		write(1, str + ((mask & addr) >> i), 1);
		mask >>= 4;
		i -= 4;
	}
}

void		put_addr(void *ptr)
{
	size_t		addr;
	size_t		mask;
	int			i;

	mask = 0xF000000000000000;
	addr = (size_t)ptr;
	i = 60;
	while (mask)
	{
		if (((mask & addr) >> i))
			break ;
		mask >>= 4;
		i -= 4;
	}
	print(mask, addr, i);
}
