/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:00:51 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/15 02:25:40 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_line(int fd, char *limit, size_t len)
{
	char	*line;

	line = readline("> ");
	if (!line || g_status == 130)
	{
		if (line)
			free(line);
		return (-1);
	}
	if (!ft_strncmp(line, limit, len + 1))
	{
		free(line);
		return (1);
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (0);
}

int	heredoc_write(int fd, char *limit, size_t len)
{
	int	res;

	setup_signals();
	while (1)
	{
		res = heredoc_line(fd, limit, len);
		if (res == -1)
		{
			setup_signals();
			return (-1);
		}
		if (res == 1)
			break ;
	}
	setup_signals();
	return (0);
}

int	heredoc_read(t_mini *shell)
{
	int	fd;

	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd < 0)
	{
		perror("heredoc");
		return (-1);
	}
	unlink(".heredoc_tmp");
	close_fd(&(shell->input));
	shell->input = fd;
	return (0);
}

int	heredoc_check_exit(void)
{
	if (g_status == 130)
	{
		g_status = 0;
		set_exit_status(1);
		return (-1);
	}
	return (0);
}
