/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ditoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salibert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 15:05:33 by salibert          #+#    #+#             */
/*   Updated: 2017/01/12 16:07:10 by salibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nbrlen(long n)
{
	int			len;

	len = 1;
	if (!n)
		return (1);
	if (n < 0)
		len++;
	while (n /= 10)
		len++;
	return (len);
}

static void		handle_no_number_after_decimal(int prec, char **str)
{
	char		*str_tmp;
	int			i;

	i = 0;
	str_tmp = ft_strnew(prec);
	while (prec--)
		str_tmp[i++] = '0';
	ft_strcat(*str, str_tmp);
	ft_strdel(&str_tmp);
}

static void		precision_smaller_than_10(double n, int prec, char **str)
{
	char		*str_tmp;
	int			prec_tmp;
	int			i;

	i = 0;
	n = n * ft_pow(10, prec);
	prec_tmp = prec - ft_nbrlen(n);
	str_tmp = ft_strnew(prec_tmp);
	while (prec_tmp--)
		str_tmp[i++] = '0';
	if ((long)((n - (long)n) * 10) > 4)
		n += 1;
	ft_strcat(*str, str_tmp);
	ft_strdel(&str_tmp);
	ft_strcat(*str, str_tmp = ft_litoa(n));
	ft_strdel(&str_tmp);
}

static int		handle_precision(double n, int prec, char **str)
{
	char		*str_tmp;

	if ((n = n - (long)n))
	{
		if (prec < 10)
			precision_smaller_than_10(n, prec, str);
		else
		{
			while (prec--)
			{
				n *= 10;
				if (!prec && (long)((n - (long)n) * 10) > 4
						&& (long)((n - (long)n) * 10) != 9)
					n += 1;
				ft_strcat(*str, str_tmp = ft_litoa(n));
				ft_strdel(&str_tmp);
				n -= (long)n;
			}
		}
	}
	else
		handle_no_number_after_decimal(prec, str);
	return (0);
}

char			*ft_ditoa(double n, int prec)
{
	char		*str;
	char		*tmp;
	size_t		len;

	if (prec < 0)
		prec = 0;
	len = ft_nbrlen((long)n) + prec + 1;
	if (!(str = ft_strnew(len)))
		return (NULL);
	if (n < 0 ? 1 : 0)
	{
		n = -n;
		str[0] = '-';
		str[1] = '\0';
	}
	ft_strcat(str, tmp = ft_litoa(n));
	ft_strdel(&tmp);
	if (prec)
	{
		ft_strcat(str, ".");
		if (handle_precision(n, prec, &str))
			return (NULL);
	}
	return (str);
}
