/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharteny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:00:51 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/11 11:00:52 by sharteny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_nonempty(char **args)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (args && args[i])
	{
		if (args[i][0] != '\0')
			k++;
		i++;
	}
	return (k);
}

static char	**compact_args(char **args, int keep)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * (keep + 1));
	if (!new)
		return (NULL);
	while (args[i])
	{
		if (args[i][0] != '\0')
			new[j++] = args[i];
		else
			free(args[i]);
		i++;
	}
	new[j] = NULL;
	free(args);
	return (new);
}

void	del_empty_args_cmd(t_cmd *cmd)
{
	int		keep;
	t_cmd	*c;

	c = cmd;
	while (c)
	{
		if (c->args)
		{
			keep = count_nonempty(c->args);
			if (keep == 0)
			{
				free_old_args(c->args);
				c->args = NULL;
			}
			else if (keep < args_len(c->args))
			{
				c->args = compact_args(c->args, keep);
			}
		}
		c = c->next;
	}
}

static void	process_tokens(t_mini *shell, t_token *tokens)
{
	t_cmd	*cmd;

	if (!tokens)
	{
		reset_status(shell->env, 2);
		return ;
	}
	cmd = parse_tokens(tokens);
	free_tokens(tokens);
	if (!cmd)
	{
		reset_status(shell->env, 2);
		return ;
	}
	shell->cmd = cmd;
	execute_expander(cmd, shell->env_arr, g_status, shell);
	del_empty_args_cmd(cmd);
	if (g_status == 130)
		g_status = 0;
	if (cmd->next)
		shell->status = execute_pipeline(shell, cmd);
	else
		shell->status = execute_cmd(shell, cmd, cmd);
	free_cmds(cmd);
	shell->cmd = NULL;
}

void	process_input(t_mini *shell, char *input)
{
	t_token	*tokens;

	if (!input || input[0] == '\0')
		return ;
	add_history(input);
	add_shell_history(shell, input);
	tokens = tokenize_line(input);
	process_tokens(shell, tokens);
}
