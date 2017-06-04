/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:45:22 by aemilien          #+#    #+#             */
/*   Updated: 2017/05/09 14:04:30 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	void	*new_s;

	new_s = ft_strnew(ft_strlen(s));
	if (new_s)
		return ((char*)ft_memcpy(new_s, (void*)s, ft_strlen(s)));
	return (NULL);
}
