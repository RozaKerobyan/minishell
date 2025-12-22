/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:00:32 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/23 00:44:46 by rkerobya         ###   ########.fr       */
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

int	setup_child_fds(t_mini *shell, t_cmd *curr)
{
	if (curr->heredoc_fd != -1)
		shell->input = curr->heredoc_fd;
	if (curr->infile)
	{
		if (open_input(shell, curr->infile) == -1)
			return (-1);
	}
	if (curr->outfile)
	{
		if (curr->append)
		{
			if (open_append(shell, curr->outfile) == -1)
				return (-1);
		}
		else
		{
			if (open_output(shell, curr->outfile) == -1)
				return (-1);
		}
	}
	return (0);
}

void	child_process(t_mini *shell, t_cmd *all, t_cmd *curr)
{
	if (setup_child_fds(shell, curr) == -1)
	{
		cleanup_minishell(shell);
		exit(1);
	}
	if (!setup_child_redir(shell, all, curr))
	{
		cleanup_minishell(shell);
		exit(1);
	}
	setup_signals_child();
	if (curr->args && curr->args[0])
		child_cmd(shell, curr);
	cleanup_minishell(shell);
	exit(0);
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
