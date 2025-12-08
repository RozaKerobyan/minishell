/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:56:53 by rkerobya          #+#    #+#             */
/*   Updated: 2025/01/26 18:04:56 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_length;
	size_t	src_length;

	dest_length = 0;
	src_length = 0;
	i = 0;
	while (dest[dest_length] != '\0' && dest_length < size)
		dest_length++;
	while (src[src_length] != '\0')
		src_length++;
	if (dest_length >= size)
		return (size + src_length);
	while ((dest_length + i) < (size - 1) && src[i] != '\0')
	{
		dest[dest_length + i] = src[i];
		i++;
	}
	if ((dest_length + i) < size)
		dest[dest_length + i] = '\0';
	return (dest_length + src_length);
}
