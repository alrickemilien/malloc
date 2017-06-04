/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:49:48 by aemilien          #+#    #+#             */
/*   Updated: 2016/11/20 13:46:30 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	*ft_memrchr(const void *s, int c, size_t n)
{
	n--;
	while (n)
	{
		if (((unsigned char*)s)[n] == (unsigned char)c)
			return ((void*)&(((unsigned char*)s)[n]));
		n--;
	}
	if (((unsigned char*)s)[n] == (unsigned char)c)
		return ((void*)&(((unsigned char*)s)[n]));
	return (NULL);
}

char			*ft_strrchr(const char *s, int c)
{
	return ((char*)ft_memrchr((void*)s, c, ft_strlen(s) + 1));
}
