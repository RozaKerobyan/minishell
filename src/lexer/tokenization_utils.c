/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharteny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 12:47:34 by sharteny          #+#    #+#             */
/*   Updated: 2025/09/21 12:47:38 by sharteny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_status(int status, char *str, int i)
{
	if (str[i] == '\'' && status == DEFAULT)
		return (SQUOTE);
	if (str[i] == '\"' && status == DEFAULT)
		return (DQUOTE);
	if (str[i] == '\'' && status == SQUOTE)
		return (DEFAULT);
	if (str[i] == '\"' && status == DQUOTE)
		return (DEFAULT);
	return (status);
}

int	is_separator(char *str, int i)
{
	if ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		return (SPACES);
	if (str[i] == '|')
		return (PIPE);
	if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	if (str[i] == '<')
		return (INPUT);
	if (str[i] == '>')
		return (TRUNC);
	if (str[i] == '\0')
		return (END);
	return (0);
}

int	save_word(t_token **tokens, char *str, int start, int i)
{
	char	*word;

	if (i <= start)
		return (0);
	word = malloc(i - start + 1);
	if (!word)
		return (1);
	ft_memcpy(word, str + start, i - start);
	word[i - start] = '\0';
	token_add_back(tokens, token_new(word, ARG));
	return (0);
}

int	save_separator(t_token **tokens, char *str, int i, t_type type)
{
	char	*sep;
	int		len;
	int		j;

	j = 0;
	if (type == APPEND || type == HEREDOC)
		len = 2;
	else
		len = 1;	
	sep = malloc(len + 1);
	if (!sep)
		return (1);
	while (j < len)
	{
		sep[j] = str[i + j];
		j++;
	}
	sep[len] = '\0';	
	token_add_back(tokens, token_new(sep, type));
	return (0);
}

void	free_tokens(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->value);
		free(list);
		list = tmp;
	}
}
