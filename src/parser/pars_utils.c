/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharteny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:48:06 by sharteny          #+#    #+#             */
/*   Updated: 2025/11/19 19:48:09 by sharteny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_type t)
{
	return (t == INPUT || t == TRUNC || t == APPEND || t == HEREDOC);
}

int	syntax_error(const char *msg, const char *token)
{
	if (token)
		printf("minishell: syntax error near unexpected token `%s'\n", token);
	else
		printf("minishell: syntax error: %s\n", msg);
	return (1);
}

int	check_syntax(t_token *t)
{
	if (!t)
		return (0);
	if (t->type == PIPE)
		return (syntax_error(NULL, "|"));
	while (t)
	{
		if (t->type == PIPE && t->next && t->next->type == PIPE)
			return (syntax_error(NULL, "|"));
		if (t->type == PIPE && t->next == NULL)
			return (syntax_error("unexpected end of input", "newline"));
		if (is_redir(t->type))
		{
			if (!t->next)
			{
				return (syntax_error(NULL, "newline"));
			}
			if (t->next->type != ARG)
			{
				return (syntax_error(NULL, t->next->value));
			}
		}
		if (is_redir(t->type) && t->next && is_redir(t->next->type))
			return (syntax_error(NULL, t->next->value));
		if (is_redir(t->type) && t->next && t->next->type == PIPE)
			return (syntax_error(NULL, "|"));
		t = t->next;
	}
	return (0);
}
