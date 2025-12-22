/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:00:51 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/15 02:26:19 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_input(t_mini *shell, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror(filename), -1);
	close_fd(&(shell->input));
	shell->input = fd;
	return (0);
}

int	open_output(t_mini *shell, char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(filename), -1);
	close_fd(&(shell->output));
	shell->output = fd;
	return (0);
}

int	open_append(t_mini *shell, char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(filename), -1);
	close_fd(&(shell->output));
	shell->output = fd;
	return (0);
}

int	redirections(t_mini *shell)
{
	if (!shell)
		return (0);
	if (shell->input != -1)
	{
		if (dup2(shell->input, STDIN_FILENO) == -1)
			return (perror("dup2"), -1);
		close_fd(&(shell->input));
	}
	if (shell->output != -1)
	{
		if (dup2(shell->output, STDOUT_FILENO) == -1)
			return (perror("dup2"), -1);
		close_fd(&(shell->output));
	}
	return (0);
}
