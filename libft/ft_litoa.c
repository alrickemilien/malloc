/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_litoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salibert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 13:07:56 by salibert          #+#    #+#             */
/*   Updated: 2017/01/12 15:54:05 by salibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(long n)
{
	int		len;

	len = 1;
	if (n < 0)
		len++;
	while (n /= 10)
		len++;
	return (len);
}

char		*ft_litoa(long n)
{
	char	*s;
	size_t	len;
	int		i;

	if (!n)
		return (ft_strdup("0"));
	len = ft_nbrlen(n);
	s = ft_strnew(len);
	if (n < 0)
		s[0] = '-';
	i = 1;
	while (n)
	{
		s[len - i] = (n < 0 ? -(n % 10) : (n % 10)) + '0';
		n /= 10;
		i++;
	}
	return (s);
}
