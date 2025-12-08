/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:23:35 by rkerobya          #+#    #+#             */
/*   Updated: 2025/01/26 18:06:44 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*d;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	d = (char *)malloc(sizeof(char) * (len + 1));
	if (!d)
		return (NULL);
	while (i < len && s[start + i])
	{
		d[i] = s[start + i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
