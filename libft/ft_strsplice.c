/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 09:45:13 by aemilien          #+#    #+#             */
/*   Updated: 2017/05/16 09:45:14 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strsplice(char *current, char *to_add, int index)
{
	int			i;
	int			j;
	int			k;
	char		*res;
	int			len;

	len = ft_strlen(current) + ft_strlen(to_add);
	if (!(res = (char*)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	res[len] = 0;
	i = 0;
	k = 0;
	while (current[i] && i < index)
		res[k++] = current[i++];
	j = 0;
	while (to_add[j])
		res[k++] = to_add[j++];
	while (current[i])
		res[k++] = current[i++];
	return (res);
}
