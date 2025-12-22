/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:06:22 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/22 12:34:49 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipe_fd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->pipe_fd)
		{
			close(tmp->pipe_fd[0]);
			close(tmp->pipe_fd[1]);
			free(tmp->pipe_fd);
			tmp->pipe_fd = NULL;
		}
		tmp = tmp->next;
	}
}

void	init_pipe_info(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->pipe_fd = NULL;
		cmd->pipe_output = (cmd->next != NULL);
		cmd = cmd->next;
	}
}

bool	create_pipes(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	init_pipe_info(cmd);
	tmp = cmd;
	while (tmp)
	{
		if (tmp->pipe_output)
		{
			tmp->pipe_fd = malloc(sizeof(int) * 2);
			if (!tmp->pipe_fd || pipe(tmp->pipe_fd) == -1)
			{
				perror("pipe");
				free(tmp->pipe_fd);
				free_pipe_fd(cmd);
				return (false);
			}
		}
		tmp = tmp->next;
	}
	return (true);
}

void	close_pipe_fds(t_cmd *cmd, t_cmd *skip)
{
	while (cmd)
	{
		if (cmd->pipe_fd && cmd != skip)
		{
			close(cmd->pipe_fd[0]);
			close(cmd->pipe_fd[1]);
		}
		cmd = cmd->next;
	}
}

bool	set_pipe_fds(t_cmd *all, t_cmd *c)
{
	if (!c)
		return (false);
	if (c->prev && c->prev->pipe_output && c->prev->pipe_fd)
	{
		if (dup2(c->prev->pipe_fd[0], STDIN_FILENO) == -1)
			return (false);
	}
	if (c->pipe_output && c->pipe_fd)
	{
		if (dup2(c->pipe_fd[1], STDOUT_FILENO) == -1)
			return (false);
	}
	close_pipe_fds(all, NULL);
	return (true);
}
