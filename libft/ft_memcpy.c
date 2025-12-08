/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:54:47 by rkerobya          #+#    #+#             */
/*   Updated: 2025/01/25 19:26:00 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*j;
	const char	*k;

	i = 0;
	j = (char *)dest;
	k = (const char *)src;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		j[i] = k[i];
		i++;
	}
	return (dest);
}
