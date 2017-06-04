/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 11:08:57 by aemilien          #+#    #+#             */
/*   Updated: 2016/11/20 15:55:23 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char*)big);
	i = 0;
	while (i < len && big[i])
	{
		while (big[i] != *little && i < len && big[i])
			i++;
		if (i == len)
			return (NULL);
		j = 0;
		while (i + j < len && big[i + j] == little[j] && little[j])
			j++;
		if (little[j] == 0)
			return ((char*)(big + i));
		if (big[i])
			i++;
	}
	return (NULL);
}
