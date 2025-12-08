/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharteny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:09:29 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/04 11:09:31 by sharteny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_prev_pipe(t_cmd *c)
{
	if (c->prev && c->prev->pipe_fd)
	{
		close(c->prev->pipe_fd[0]);
		close(c->prev->pipe_fd[1]);
		free(c->prev->pipe_fd);
		c->prev->pipe_fd = NULL;
	}
}

int	wait_pipeline(t_cmd *cmd)
{
	int	status;
	int	last;

	last = 0;
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				last = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last = 128 + WTERMSIG(status);
		}
		cmd = cmd->next;
	}
	set_exit_status(last);
	return (last);
}

int	execute_pipeline(t_mini *shell, t_cmd *cmd)
{
	t_cmd *c;
	pid_t pid;
	
	if (!cmd || !create_pipes(cmd))
		return (1);
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
			return (1);
		}
		if (pid == 0)
		{
			setup_signals_child();
			child_process(shell, cmd, c);
		}
		setup_signals();
		c->pid = pid;
		close_prev_pipe(c);
		c = c->next;
	}
	free_pipe_fd(cmd);
	return (wait_pipeline(cmd));
}
