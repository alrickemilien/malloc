/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salibert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 19:36:44 by salibert          #+#    #+#             */
/*   Updated: 2017/02/08 19:36:50 by salibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	count_size(char **str)
{
	int			i;
	double		m;

	i = 0;
	m = 0.1;
	while (ft_isdigit((*str)[i]))
	{
		m *= 10;
		i++;
	}
	return (m);
}

static double	get_integer(char **str, int n)
{
	double		m;
	double		nbr;

	nbr = 0;
	m = count_size(str);
	while (ft_isdigit(**str))
	{
		if (n)
			nbr += m * (double)(**str - '0');
		else
			nbr -= m * (double)(**str - '0');
		m /= 10;
		(*str)++;
	}
	return (nbr);
}

double			get_decimal(char **str, int n)
{
	double		m;
	double		nbr;

	nbr = 0;
	m = 0.1;
	if (**str == '.')
	{
		(*str)++;
		while (ft_isdigit(**str))
		{
			if (n)
				nbr += m * (double)(**str - '0');
			else
				nbr -= m * (double)(**str - '0');
			m *= 0.1;
			(*str)++;
		}
	}
	return (nbr);
}

double			ft_atod(char **str)
{
	int			i;
	int			n;

	i = 0;
	n = 1;
	while ((*str)[i] == ' ' || (*str)[i] == '\n'
			|| (*str)[i] == '\t' || (*str)[i] == '\r' || (*str)[i] == '\v')
		i++;
	if ((*str)[i] == '-' || (*str)[i] == '+')
	{
		if ((*str)[i] == '-')
			n = 0;
		i++;
	}
	*str += i;
	return (get_integer(str, n) + get_decimal(str, n));
}
