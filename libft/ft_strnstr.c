/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:01:45 by rkerobya          #+#    #+#             */
/*   Updated: 2025/01/26 18:08:59 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i + j] == needle[j])
		{
			while (haystack[i + j] == needle[j] && \
(i + j) < len && needle[j] != '\0')
			{
				j++;
			}
			if (needle[j] == '\0')
			{
				return ((char *)haystack + i);
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
