/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 18:56:50 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/20 18:59:37 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin_child(t_mini *shell, t_cmd *curr)
{
	if (builtins(curr->args[0]))
		exit(execute_builtins(shell, curr->args));
}

char	*resolve_cmd_path(t_mini *shell, t_cmd *curr)
{
	char	*path;

	path = find_cmd_path(curr->args[0], shell->env);
	if (!path)
	{
		if (ft_strchr(curr->args[0], '/'))
		{
			if (access(curr->args[0], F_OK) == -1)
				minishell_error(curr->args[0], "No such file or directory");
			else if (check_directory(curr->args[0]))
				minishell_error(curr->args[0], "Is a directory");
			else
				minishell_error(curr->args[0], "Permission denied");
			exit(127);
		}
		minishell_error(curr->args[0], "command not found");
		exit(127);
	}
	return (path);
}

void	exec_external_cmd(t_mini *shell, t_cmd *curr, char *cmd_path)
{
	if (check_directory(cmd_path))
	{
		minishell_error(curr->args[0], "Is a directory");
		free(cmd_path);
		exit(126);
	}
	if (access(cmd_path, X_OK) != 0)
	{
		minishell_error(curr->args[0], "Permission denied");
		free(cmd_path);
		exit(126);
	}
	execve(cmd_path, curr->args, shell->env_arr);
	minishell_error(curr->args[0], strerror(errno));
	free(cmd_path);
	exit(126);
}

void	child_cmd(t_mini *shell, t_cmd *curr)
{
	char	*cmd_path;

	exec_builtin_child(shell, curr);
	cmd_path = resolve_cmd_path(shell, curr);
	exec_external_cmd(shell, curr, cmd_path);
}
