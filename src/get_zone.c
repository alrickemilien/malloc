/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_zone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:09:16 by aemilien          #+#    #+#             */
/*   Updated: 2018/08/18 14:12:12 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** This function identfys the zone bi its size,
** returnig an int corresponding to the zone between :
** __MALLOC_TINY_LIMIT__ - __MALLOC_SMALL__ - __MALLOC_SMALL_LIMIT__
*/

int	get_zone(size_t size)
{
	if (size < __MALLOC_TINY_LIMIT__)
		return (__MALLOC_TINY__);
	if (size < __MALLOC_SMALL_LIMIT__)
		return (__MALLOC_SMALL__);
	return (__MALLOC_LARGE__);
}
