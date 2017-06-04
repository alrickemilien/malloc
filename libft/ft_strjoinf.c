/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salibert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 14:49:01 by salibert          #+#    #+#             */
/*   Updated: 2016/11/14 15:57:10 by salibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_free(char const *s1, char const *s2, char c)
{
	if (c == 'L')
		free((char*)s1);
	if (c == 'R')
		free((char*)s2);
	if (c == 'B')
	{
		free((char*)s1);
		free((char*)s2);
	}
}

char			*ft_strjoinf(char const *s1, const char *s2, char c)
{
	char		*str;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!(str = (char *)malloc(sizeof(str) * (ft_strlen(s1)
		+ ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	ft_free(s1, s2, c);
	return (str);
}
