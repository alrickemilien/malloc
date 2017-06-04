/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:39:32 by aemilien          #+#    #+#             */
/*   Updated: 2016/11/23 12:59:05 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_strlentrim(char const *s)
{
	size_t		i;

	if (*s == '\0')
		return (0);
	i = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	s--;
	while ((*s == ' ' || *s == '\t' || *s == '\n') && i)
	{
		s--;
		i--;
	}
	return (i);
}

static	int		ft_strstart(const char *s)
{
	int		i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	return (i);
}

char			*ft_strtrim(char const *s)
{
	char	*str;

	if (s)
	{
		str = ft_strsub(s, ft_strstart(s), ft_strlentrim(s));
		return (str);
	}
	return (NULL);
}
