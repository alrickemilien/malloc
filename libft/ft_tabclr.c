/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 16:08:58 by aemilien          #+#    #+#             */
/*   Updated: 2016/11/20 17:38:22 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabclr(void ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i])
	{
		ft_memdel((void**)(&((*((unsigned char)tab))[i])));
		i++;
	}
	ft_memdel((void**)(&((*((unsigned char)tab))[i])));
	*tab = NULL;
}
