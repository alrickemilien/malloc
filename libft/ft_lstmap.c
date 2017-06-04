/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 13:26:08 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/04 13:42:06 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;

	if (!lst || !f)
		return (NULL);
	new_lst = ft_lstnew(NULL, 0);
	if (new_lst)
	{
		new_lst = f(lst);
		if (lst->next)
			new_lst->next = ft_lstmap(lst->next, f);
	}
	return (new_lst);
}
