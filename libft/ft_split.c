/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:30:18 by rkerobya          #+#    #+#             */
/*   Updated: 2025/02/10 17:31:12 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**array_free(char **str, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

static int	count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			i++;
		}
		else
		{
			count++;
			while (s[i] && s[i] != c)
			{
				i++;
			}
		}
	}
	return (count);
}

static char	*get_words(char *word, char const *j, int n, int length)
{
	int	i;

	i = 0;
	while (length > 0)
	{
		word[i] = j[n - length];
		i++;
		length--;
	}
	word[i] = '\0';
	return (word);
}

static char	**split_words(char const *ptr, char c, char **ss, int length_word)
{
	int	i;
	int	word;
	int	word_length;

	i = 0;
	word = 0;
	word_length = 0;
	while (word < length_word)
	{
		while (ptr[i] && ptr[i] == c)
			i++;
		while (ptr[i] && ptr[i] != c)
		{
			i++;
			word_length++;
		}
		ss[word] = (char *)malloc(sizeof(char) * (word_length + 1));
		if (!ss[word])
			return (array_free(ss, word));
		get_words(ss[word], ptr, i, word_length);
		word_length = 0;
		word++;
	}
	ss[word] = 0;
	return (ss);
}

char	**ft_split(char const *s, char c)
{
	char			**str;
	unsigned int	words_length;

	if (!s)
		return (0);
	words_length = count_words(s, c);
	str = (char **)malloc(sizeof(char *) * (words_length + 1));
	if (!str)
		return (0);
	str = split_words(s, c, str, words_length);
	return (str);
}
