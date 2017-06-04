/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:52:30 by aemilien          #+#    #+#             */
/*   Updated: 2016/11/19 18:04:35 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	if (n > ft_strlen(src))
		n = ft_strlen(src);
	dest[ft_strlen(dest) + n] = 0;
	ft_strncpy(dest + ft_strlen(dest), src, n);
	return (dest);
}
