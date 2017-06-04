/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrepeat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 10:43:41 by aemilien          #+#    #+#             */
/*   Updated: 2017/05/16 09:44:25 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrepeat(char *s, int n)
{
	char	*ret;
	int		len;
	int		i;
	int		j;
	int		k;

	if (n <= 0)
		return (ft_strdup(""));
	len = ft_strlen(s);
	if (!(ret = malloc(sizeof(char*) * (len * n + 1))))
		return (NULL);
	ret[len * n] = 0;
	i = 0;
	k = 0;
	while (i < n)
	{
		j = 0;
		while (s[j])
			ret[k++] = s[j++];
		i++;
	}
	return (ret);
}
