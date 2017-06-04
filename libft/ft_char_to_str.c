/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 10:31:05 by aemilien          #+#    #+#             */
/*   Updated: 2017/05/16 09:45:37 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_char_to_str(unsigned char c)
{
	char	*ret;

	if (!(ret = malloc(sizeof(unsigned char*) * 2)))
		return (NULL);
	ret[0] = c;
	ret[1] = '\0';
	return (ret);
}
