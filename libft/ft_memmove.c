/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:36:37 by aemilien          #+#    #+#             */
/*   Updated: 2016/11/19 17:53:38 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if ((size_t)(dest - src) < n)
	{
		n--;
		while (n)
		{
			((unsigned char*)dest)[n] = ((unsigned char*)src)[n];
			n--;
		}
		((unsigned char*)dest)[n] = ((unsigned char*)src)[n];
	}
	else
		return (ft_memcpy(dest, src, n));
	return (dest);
}
