/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:56:32 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/23 00:08:24 by rkerobya         ###   ########.fr       */
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
	cmd->heredoc_fd = -1;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

void	free_args_array(char **args, int n)
{
	if (!args || n <= 0)
		return ;
	while (--n >= 0)
		free(args[n]);
	free(args);
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
	{
		free_args_array(cmd->args, n);
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
