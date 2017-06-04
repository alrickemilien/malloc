/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtrim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salibert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 09:41:05 by salibert          #+#    #+#             */
/*   Updated: 2017/01/24 09:43:25 by salibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_dtrim(double min, double max, double nb)
{
	if (min > nb)
		return (min);
	else if (max < nb)
		return (max);
	else
		return (nb);
}
