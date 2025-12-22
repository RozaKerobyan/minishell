/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:00:51 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/23 00:44:05 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_pipeline(t_cmd *cmd)
{
	int	status;
	int	last;
	int	sig;

	last = 0;
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				last = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				last = 128 + sig;
				if (sig == SIGINT)
					write(1, "\n", 1);
			}
		}
		cmd = cmd->next;
	}
	set_exit_status(last);
	return (last);
}

int	create_child_processes(t_mini *shell, t_cmd *cmd)
{
	t_cmd	*c;
	pid_t	pid;

	c = cmd;
	while (c)
	{
		setup_signals_parent_exec();
		pid = fork();
		if (pid == -1)
		{
			setup_signals();
			perror("fork");
			free_pipe_fd(cmd);
			return (0);
		}
		if (pid == 0)
		{
			setup_signals_child();
			child_process(shell, cmd, c);
		}
		c->pid = pid;
		close_prev_pipe(c);
		c = c->next;
	}
	return (1);
}

int	set_redir_pipeline(t_mini *shell, t_cmd *cmd)
{
	t_cmd	*c;

	c = cmd;
	while (c)
	{
		if (c->heredoc_limiter)
		{
			if (heredoc(shell, c->heredoc_limiter) == -1)
			{
				if (g_status == 130)
					return (130);
				return (1);
			}
			c->heredoc_fd = shell->input;
			shell->input = -1;
		}
		c = c->next;
	}
	if (!prepare_output_files(cmd))
		return (1);
	if (!create_pipes(cmd))
		return (1);
	return (0);
}

int	run_pipeline(t_mini *shell, t_cmd *cmd)
{
	t_cmd	*c;
	int		ret;

	if (!create_child_processes(shell, cmd))
		return (1);
	c = cmd;
	while (c)
	{
		if (c->heredoc_fd != -1)
		{
			close(c->heredoc_fd);
			c->heredoc_fd = -1;
		}
		c = c->next;
	}
	free_pipe_fd(cmd);
	ret = wait_pipeline(cmd);
	setup_signals();
	return (ret);
}

int	execute_pipeline(t_mini *shell, t_cmd *cmd)
{
	int	setup_result;

	if (!cmd)
		return (1);
	setup_result = set_redir_pipeline(shell, cmd);
	if (setup_result != 0)
		return (setup_result);
	return (run_pipeline(shell, cmd));
}
