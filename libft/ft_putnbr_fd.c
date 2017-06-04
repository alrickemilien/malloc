/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:37:12 by aemilien          #+#    #+#             */
/*   Updated: 2016/11/19 18:13:47 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		m;

	if (n < 0)
		ft_putchar_fd('-', fd);
	m = 1;
	while ((n / m) >= 10 || n / m <= -10)
		m *= 10;
	while (m >= 1)
	{
		if (n < 0)
			ft_putchar_fd(-((n / m) % 10) + 48, fd);
		if (n > 0)
			ft_putchar_fd((n / m) % 10 + 48, fd);
		if (n == 0)
			ft_putchar_fd(48, fd);
		m = m / 10;
	}
}
