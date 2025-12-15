/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:27:18 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/15 02:27:20 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long int	long_len(long i)
{
	int	len;

	len = 0;
	if (i <= 0)
	{
		len = 1;
	}
	while (i != 0)
	{
		len++;
		i /= 10;
	}
	return (len);
}

static char	*str(char *s, long nb, long int length)
{
	long	digit;

	while (nb > 0)
	{
		digit = nb % 10;
		s[length] = 48 + digit;
		nb /= 10;
		length--;
	}
	return (s);
}

char	*ft_itoa_long(long n)
{
	long	nb;
	long	len;
	char	*d;

	len = long_len(n);
	d = (char *)malloc(sizeof(char) * (len + 1));
	if (!d)
		return (NULL);
	d[len--] = '\0';
	if (n == 0)
		d[0] = '0';
	if (n < 0)
	{
		d[0] = '-';
		nb = -n;
	}
	else
		nb = n;
	str(d, nb, len);
	return (d);
}
