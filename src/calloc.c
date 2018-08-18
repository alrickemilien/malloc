/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 11:48:30 by aemilien          #+#    #+#             */
/*   Updated: 2018/08/18 11:48:32 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t nmemb, size_t size)
{
	void				*ret;

	ret = malloc(size * nmemb);
	ft_memset(ret, 0, size);
	return (ret);
}
