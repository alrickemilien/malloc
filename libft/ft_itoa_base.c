/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salibert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 13:55:54 by salibert          #+#    #+#             */
/*   Updated: 2017/05/12 14:14:39 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_size(unsigned long long nb, int base)
{
	int		i;

	i = 1;
	if (base < 2 || base > 16)
		return (0);
	while (nb /= base)
		i++;
	return (i);
}

char		*ft_itoa_base(unsigned long long nb, int base)
{
	int		size;
	int		i;
	char	*tab;
	char	*nbr;

	if (!nb)
		return (ft_strdup("0"));
	if (!(size = ft_size(nb, base)))
		return (0);
	tab = ft_strdup("0123456789abcdef");
	nbr = ft_strnew(size);
	i = 1;
	while (nb)
	{
		nbr[size - i] = tab[nb % base];
		i++;
		nb /= base;
	}
	ft_strdel(&tab);
	return (nbr);
}
