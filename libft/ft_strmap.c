/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:46:13 by aemilien          #+#    #+#             */
/*   Updated: 2016/11/19 18:03:50 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*new_str;

	if (s == NULL || f == NULL)
		return (NULL);
	new_str = ft_strnew(ft_strlen(s));
	if (new_str != NULL)
	{
		i = 0;
		while (s[i] != '\0')
		{
			new_str[i] = (char)f(s[i]);
			i++;
		}
		return (new_str);
	}
	return (new_str);
}
