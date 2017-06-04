/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:35:11 by aemilien          #+#    #+#             */
/*   Updated: 2016/11/19 18:09:27 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*new_str;
	size_t		i;

	if (s == NULL)
		return (NULL);
	new_str = ft_strnew(len);
	if (new_str)
	{
		i = 0;
		while (i < len && s[start + i])
		{
			new_str[i] = s[start + i];
			i++;
		}
		return (new_str);
	}
	else
		return (NULL);
}
