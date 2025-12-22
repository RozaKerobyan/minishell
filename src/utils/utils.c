/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:27:39 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/23 00:40:01 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int *fd)
{
	if (!fd || *fd == -1)
	{
		return ;
	}
	close(*fd);
	*fd = -1;
}

int	args_len(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	check_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

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
