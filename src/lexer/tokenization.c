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

t_token	*token_new(char *value, t_type type)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = value;
	tok->type = type;
	tok->next = NULL;
	return (tok);
}

void	token_add_back(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*tokenize_line(char *line)
{
	t_token	*tokens;
	int		i;
	int		start;
	int		status;

	tokens = NULL;
	i = 0;
	start = 0;
	status = DEFAULT;
	while (line[i])
	{
		status = set_status(status, line, i);
		if (status == DEFAULT)
		{
			int type = is_separator(line, i);
			if (type)
			{
				if (i != start)
					save_word(&tokens, line, start, i);
				if (type != SPACES)
					save_separator(&tokens, line, i, type);
				if (type == APPEND || type == HEREDOC)
					i += 2;
				else
					i += 1;
				start = i;
				continue;
			}
		}
		i++;
	}
	if (i != start)
		save_word(&tokens, line, start, i);
	if (status != DEFAULT)
	{
		free_tokens(tokens);
		printf("minishell: unexpected EOF while looking for matching '\"'\n");
		return (NULL);
	}
	t_token *tmp = tokens;
	while (tmp)
	{
		tmp = tmp->next;
	}
	return (tokens);
}
