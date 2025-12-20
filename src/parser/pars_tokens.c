/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:30:14 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/20 21:34:05 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_regular_token(t_token **tok, t_cmd *cur)
{
	if ((*tok)->type == ARG)
		add_arg(cur, (*tok)->value);
	else if (is_redir((*tok)->type))
		handle_redir(cur, tok);
}

t_cmd	*handle_pipe_token(t_token **tok, t_cmd *cur)
{
	cur->next = new_cmd();
	if (!cur->next)
		return (NULL);
	cur->next->prev = cur;
	cur = cur->next;
	*tok = (*tok)->next;
	return (cur);
}

t_cmd	*parse_tokens_run(t_token *tok, t_cmd *head)
{
	t_cmd	*cur;

	cur = head;
	while (tok)
	{
		if (tok->type == PIPE)
		{
			cur = handle_pipe_token(&tok, cur);
			if (!cur)
			{
				free_cmds(head);
				return (NULL);
			}
			continue ;
		}
		else
			handle_regular_token(&tok, cur);
		tok = tok->next;
	}
	return (head);
}

t_cmd	*parse_tokens(t_token *tok)
{
	t_cmd	*head;

	head = new_cmd();
	if (!head)
		return (NULL);
	if (!tok || check_syntax(tok))
	{
		free_cmds(head);
		return (NULL);
	}
	return (parse_tokens_run(tok, head));
}
