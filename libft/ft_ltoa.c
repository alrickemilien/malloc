/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 08:54:59 by aemilien          #+#    #+#             */
/*   Updated: 2017/05/10 11:52:29 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(long n)
{
	int		len;

	len = 0;
	if (!n)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char		*ft_ltoa(long n)
{
	char	*s;
	size_t	len;

	if (!n)
		return (ft_strdup("0"));
	len = ft_nbrlen(n) + 1;
	if (!(s = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	if (n < 0)
		s[0] = '-';
	s[len - 1] = '\0';
	while (n)
	{
		len--;
		if (n > 0)
			s[len - 1] = (n % 10) + '0';
		else
			s[len - 1] = -(n % 10) + '0';
		n /= 10;
	}
	return (s);
}
