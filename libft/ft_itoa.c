/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:23:47 by rkerobya          #+#    #+#             */
/*   Updated: 2025/02/06 16:11:26 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	length(int i)
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
		i = i / 10;
	}
	return (len);
}

static char	*str(char *s, unsigned int nb, long int length)
{
	while (nb > 0)
	{
		s[length] = 48 + (nb % 10);
		length--;
		nb = nb / 10;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	int				sign;
	long int		len;
	char			*d;

	sign = 1;
	len = length(n);
	d = (char *)malloc(sizeof(char) * (len + 1));
	if (!d)
		return (NULL);
	d[len--] = '\0';
	if (n == 0)
		d[0] = '0';
	if (n < 0)
	{
		sign *= -1;
		nb = n * -1;
		d[0] = '-';
	}
	else
		nb = n;
	d = str(d, nb, len);
	return (d);
}
