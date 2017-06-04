/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:34:32 by aemilien          #+#    #+#             */
/*   Updated: 2016/11/19 18:05:15 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t size)
{
	size_t		i;

	if (size < ft_strlen(src))
		return ((char*)ft_memcpy((void*)dest, (void*)src, size));
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < size)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}
