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
	if (!new_args) // added for clean
	{
		while (--n >= 0)
			free(new_args[n]);
		free(new_args);
		return ;
	}
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

char	*remove_quotes_str(const char *str)
{
	int		i;
	int		j;
	char	*result;
	char	quote;

	if (!str)
		return (NULL);

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
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
	if (unquoted != filename)
		free(unquoted);
}
