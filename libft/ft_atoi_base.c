/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 14:47:15 by aemilien          #+#    #+#             */
/*   Updated: 2017/02/02 11:52:51 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_value(char *str, int base)
{
	int		i;

	i = 0;
	while (ft_isdigit(str[i]) | ft_isalpha(str[i]))
		i++;
	return (ft_pow(base, i - 1));
}

int			ft_atoi_base(char *str, int base)
{
	int		nbr;
	int		signe;
	int		d;

	nbr = 0;
	while (*str == '\t' || *str == '\n' || *str == '\r' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		signe = (base == 10 && *str == '-') ? -1 : 1;
		str++;
	}
	d = set_value(str, base);
	while (ft_isalpha(*str) || ft_isdigit(*str))
	{
		if (ft_isdigit(*str))
			nbr += (*str - '0') * d;
		else if (ft_ismin(*str))
			nbr += (*str - 'a' + 10) * d;
		else if (ft_ismaj(*str))
			nbr += (*str - 'A' + 10) * d;
		d /= base;
		str++;
	}
	return (nbr * signe);
}
