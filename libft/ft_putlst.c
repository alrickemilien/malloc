/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 17:00:05 by aemilien          #+#    #+#             */
/*   Updated: 2016/11/20 17:00:28 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlst(t_list *lst)
{
	if (!lst)
		return ;
	while (lst->next)
	{
		ft_putstr("{ ");
		if (lst->content_size == sizeof(int))
			ft_putnbr((int)(lst->content));
		if (lst->content_size == sizeof(char))
			ft_putchar((char)(lst->content));
		if (lst->content_size == sizeof(char*))
			ft_putstr((char*)(lst->content));
		ft_putstr(" } -> ");
		lst = lst->next;
	}
	ft_putstr("NULL\n");
}
