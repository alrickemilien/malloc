/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:52:55 by aemilien          #+#    #+#             */
/*   Updated: 2016/11/18 15:58:16 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_strtab(size_t size)
{
	char		**tab;

	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (size + 1))))
		return (NULL);
	return (tab);
}

static	size_t	ft_nbrwords(char const *s, char c)
{
	int			i;
	size_t		n;

	i = 0;
	n = 1;
	while (s[i])
	{
		if (s[i] == c && (s[i + 1] != c && s[i + 1] != '\0'))
			n++;
		i++;
	}
	return (n);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t		i;
	size_t		n;
	char		**tab;

	if (!s)
		return (NULL);
	while (*s == c)
		s++;
	tab = ft_strtab(ft_nbrwords(s, c));
	if (!tab)
		return (NULL);
	n = 0;
	while (*s)
	{
		i = 0;
		while (s[i] != c && s[i])
			i++;
		tab[n] = ft_strsub(s, 0, i);
		while (s[i] == c && s[i])
			i++;
		s = s + i;
		n++;
	}
	return (tab);
}
