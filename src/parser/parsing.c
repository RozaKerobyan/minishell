/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharteny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:56:32 by sharteny          #+#    #+#             */
/*   Updated: 2025/11/11 18:56:35 by sharteny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->is_heredoc = 0;
	cmd->type = NULL;
	cmd->pipe_fd = NULL;
	cmd->pipe_output = 0;
	cmd->pid = -1;
	cmd->heredoc_limiter = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

void	add_arg(t_cmd *cmd, const char *value)
{
	int		n;
	int		i;
	char	**new_args;

	n = 0;
	i = 0;
	if (cmd->args)
		while (cmd->args[n])
			n++;
	new_args = malloc(sizeof(char *) * (n + 2));
	if (!new_args)
		return ;
	while (i < n)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[n] = ft_strdup(value);
	new_args[n + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

t_cmd	*parse_tokens(t_token *tok)
{
	t_cmd	*head;
	t_cmd	*cur;

	head = new_cmd();
	cur = head;
	if (!tok)
		return (NULL);
	if (check_syntax(tok))
		return (NULL);
	while (tok)
	{
		if (tok->type == ARG)
			add_arg(cur, tok->value);
		else if (is_redir(tok->type))
			handle_redir(cur, &tok);
		else if (tok->type == PIPE)
		{
			cur->next = new_cmd();
			if (cur->next)
				cur->next->prev = cur;
			cur = cur->next;
		}
		tok = tok->next;
	}
	return (head);
}

void	handle_redir(t_cmd *cur, t_token **tok)
{
	t_token	*redir_token;
	char	*filename;

	if (!(*tok) || !(*tok)->next)
		return ;
	redir_token = *tok;
	filename = (*tok)->next->value;
	*tok = (*tok)->next;
	if (redir_token->type == INPUT)
	{
		cur->infile = ft_strdup(filename);
	}
	else if (redir_token->type == TRUNC)
	{
		cur->append = 0;
		cur->outfile = ft_strdup(filename);
	}
	else if (redir_token->type == APPEND)
	{
		cur->append = 1;
		cur->outfile = ft_strdup(filename);
	}
	else if (redir_token->type == HEREDOC)
	{
		cur->is_heredoc = 1;
		cur->heredoc_limiter = ft_strdup(filename);
	}
}
