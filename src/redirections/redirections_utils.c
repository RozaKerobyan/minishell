/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:28:55 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/20 19:12:10 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	redir_type(char *s)
{
	if (!s)
		return (0);
	if (!ft_strncmp(s, "<<", 2))
		return (HEREDOC);
	if (!ft_strncmp(s, ">>", 2))
		return (APPEND);
	if (!ft_strncmp(s, "<", 1))
		return (INPUT);
	if (!ft_strncmp(s, ">", 1))
		return (TRUNC);
	return (0);
}

int	handle_heredoc_infile(t_mini *shell, t_cmd *cmd)
{
	if (cmd->heredoc_limiter)
	{
		if (heredoc(shell, cmd->heredoc_limiter) == -1)
		{
			if (g_status == 130)
				return (-2);
			return (-1);
		}
	}
	if (cmd->infile)
	{
		if (open_input(shell, cmd->infile) == -1)
			return (-1);
	}
	return (0);
}

int	prepare_output_files(t_cmd *cmd)
{
	t_cmd	*c;
	int		fd;

	c = cmd;
	while (c)
	{
		if (c->outfile)
		{
			if (c->append)
				fd = open(c->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd = open(c->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(c->outfile);
				return (0);
			}
			close(fd);
		}
		c = c->next;
	}
	return (1);
}

int	setup_redir(t_mini *shell, t_cmd *cmd)
{
	if (!shell || !cmd)
		return (0);
	if (cmd->heredoc_limiter)
	{
		if (heredoc(shell, cmd->heredoc_limiter) == -1)
		{
			if (g_status == 130)
				return (-2);
			return (-1);
		}
	}
	if (cmd->infile)
		if (open_input(shell, cmd->infile) == -1)
			return (-1);
	if (cmd->outfile && !cmd->append)
		if (open_output(shell, cmd->outfile) == -1)
			return (-1);
	if (cmd->outfile && cmd->append)
		if (open_append(shell, cmd->outfile) == -1)
			return (-1);
	return (0);
}

int	setup_child_redir(t_mini *shell, t_cmd *all, t_cmd *curr)
{
	if (!set_pipe_fds(all, curr))
		return (0);
	if (redirections(shell) == -1)
		return (0);
	return (1);
}
