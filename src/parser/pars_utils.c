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
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd((char *)token, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("syntax error: ", STDERR_FILENO);
		ft_putstr_fd((char *)msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	set_exit_status(2);
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
				return (syntax_error(NULL, "newline"));
			if (t->next->type != ARG)
				return (syntax_error(NULL, t->next->value));
		}
		if (is_redir(t->type) && t->next && is_redir(t->next->type))
			return (syntax_error(NULL, t->next->value));
		if (is_redir(t->type) && t->next && t->next->type == PIPE)
			return (syntax_error(NULL, "|"));
		t = t->next;
	}
	return (0);
}

void	norm(t_cmd *cur, t_token *redir_token, char *unquoted)
{
	if (redir_token->type == INPUT)
	{
		free(cur->infile);
		cur->infile = ft_strdup(unquoted);
	}
	else if (redir_token->type == TRUNC)
	{
		free(cur->outfile);
		cur->append = 0;
		cur->outfile = ft_strdup(unquoted);
	}
	else if (redir_token->type == APPEND)
	{
		free(cur->outfile);
		cur->append = 1;
		cur->outfile = ft_strdup(unquoted);
	}
	else if (redir_token->type == HEREDOC)
	{
		free(cur->heredoc_limiter);
		cur->is_heredoc = 1;
		cur->heredoc_limiter = ft_strdup(unquoted);
	}
}

void	handle_redir(t_cmd *cur, t_token **tok)
{
	t_token	*redir_token;
	char	*filename;
	char	*unquoted;

	if (!(*tok) || !(*tok)->next)
		return ;
	redir_token = *tok;
	filename = (*tok)->next->value;
	unquoted = remove_quotes_str(filename);
	if (!unquoted)
		unquoted = filename;
	*tok = (*tok)->next;
	if (is_redir(redir_token->type))
		norm(cur, redir_token, unquoted);
	if (unquoted != filename)
		free(unquoted);
}
