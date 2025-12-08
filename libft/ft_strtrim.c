/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:17:56 by rkerobya          #+#    #+#             */
/*   Updated: 2025/01/26 18:08:35 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	start = 0;
	end = ft_strlen(s1) - 1;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end >= start && ft_strchr(set, s1[end]))
		end--;
	if (start > end)
		return (ft_substr("", 0, 0));
	str = ft_substr(s1, start, end - start + 1);
	return (str);
}
