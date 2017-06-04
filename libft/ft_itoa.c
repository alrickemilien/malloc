/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:36:26 by aemilien          #+#    #+#             */
/*   Updated: 2017/05/12 19:15:03 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sizeofnbr(long long n, long long *m)
{
	int		size;

	size = 1;
	if (n < 0)
		size++;
	*m = 1;
	while (n / *m >= 10 || n / *m <= -10)
	{
		*m *= 10;
		size++;
	}
	return (size);
}

char		*ft_itoa(long long n)
{
	char			*str;
	long long		m;
	int				i;

	if (!n)
		return (ft_strdup("0"));
	str = ft_strnew(ft_sizeofnbr(n, &m));
	if (!str)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		str[0] = '-';
		i = 1;
	}
	while (m > 0)
	{
		if (n >= 0)
			str[i] = ((n / m) % 10) + 48;
		if (n < 0)
			str[i] = -((n / m) % 10) + 48;
		m = m / 10;
		i++;
	}
	return (str);
}
