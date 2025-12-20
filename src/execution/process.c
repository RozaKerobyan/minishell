/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:00:32 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/20 19:14:03 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

void	child_process(t_mini *shell, t_cmd *all, t_cmd *curr)
{
	if (!setup_child_redir(shell, all, curr))
		exit(1);
	setup_signals_child();
	if (curr->args && curr->args[0])
		child_cmd(shell, curr);
	exit(0);
}

int	setup_and_valid(t_mini *shell, t_cmd *curr, char **cmd_path)
{
	*cmd_path = find_cmd_path(curr->args[0], shell->env);
	if (!*cmd_path)
		return (cmd_error(curr->args[0]));
	if (check_directory(*cmd_path))
	{
		minishell_error(curr->args[0], "Is a directory");
		free(*cmd_path);
		return (126);
	}
	return (0);
}

int	fork_and_execute(t_mini *shell, t_cmd *all, t_cmd *curr, char *cmd_path)
{
	pid_t	pid;
	int		status;

	setup_signals_parent_exec();
	pid = fork();
	if (pid == -1)
	{
		setup_signals();
		free(cmd_path);
		return (fork_error(NULL));
	}
	if (pid == 0)
	{
		setup_signals_child();
		child_process(shell, all, curr);
	}
	curr->pid = pid;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		write(1, "\n", 1);
	setup_signals();
	return (process_status(status));
}

int	execute_external(t_mini *shell, t_cmd *all, t_cmd *curr)
{
	char	*cmd_path;
	int		validation_result;
	int		execution_result;

	validation_result = setup_and_valid(shell, curr, &cmd_path);
	if (validation_result != 0)
		return (validation_result);
	execution_result = fork_and_execute(shell, all, curr, cmd_path);
	free(cmd_path);
	return (execution_result);
}
