/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:32:09 by aemilien          #+#    #+#             */
/*   Updated: 2016/11/19 18:13:17 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;

	if (!*needle)
		return ((char*)haystack);
	while (*haystack)
	{
		haystack = ft_strchr(haystack, *needle);
		if (!haystack)
			return (NULL);
		i = 0;
		while (haystack[i] == needle[i] && haystack[i])
			i++;
		if (!needle[i])
			return ((char*)haystack);
		haystack++;
	}
	return (NULL);
}
