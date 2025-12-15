/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:00:51 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/15 02:25:45 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_finalize(t_mini *shell)
{
	int	fd;

	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd < 0)
	{
		perror("heredoc");
		unlink(".heredoc_tmp");
		return (-1);
	}
	unlink(".heredoc_tmp");
	close_fd(&(shell->input));
	shell->input = fd;
	return (0);
}

int	heredoc(t_mini *shell, char *limit)
{
	int		fd;
	size_t	len;
	int		result;

	if (!limit || heredoc_check_exit() == -1)
		return (-1);
	len = ft_strlen(limit);
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("heredoc"), -1);
	setup_signals();
	result = heredoc_write(fd, limit, len);
	setup_signals();
	close(fd);
	if (result == -1 || g_status == 130)
	{
		g_status = 0;
		unlink(".heredoc_tmp");
		set_exit_status(1);
		return (-1);
	}
	return (heredoc_finalize(shell));
}
