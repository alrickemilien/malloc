/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salibert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 15:06:36 by salibert          #+#    #+#             */
/*   Updated: 2016/11/14 15:11:02 by salibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_trim(int min, int max, int nb)
{
	if (min > nb)
		return (min);
	else if (max < nb)
		return (max);
	else
		return (nb);
}
