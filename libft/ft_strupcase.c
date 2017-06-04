/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 17:31:50 by aemilien          #+#    #+#             */
/*   Updated: 2017/05/12 17:45:43 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strupcase(char *src)
{
	int		i;
	char	*s;
	int		len;

	len = (int)ft_strlen(src);
	if (!(s = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s[len] = 0;
	i = 0;
	while (src[i])
	{
		if (src[i] >= 97 && src[i] <= 122)
			s[i] = src[i] - 32;
		else
			s[i] = src[i];
		i++;
	}
	return (s);
}
