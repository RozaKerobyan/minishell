/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:50:28 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/20 19:17:02 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_mini *shell, t_cmd *all, t_cmd *curr)
{
	int	status;
	int	redir_result;

	if (!curr->args || !curr->args[0])
		return (0);
	redir_result = setup_redir(shell, curr);
	if (redir_result == -2)
		return (1);
	if (redir_result == -1)
		return (set_exit_status(1), 1);
	if (builtins(curr->args[0]))
	{
		status = execute_builtins(shell, curr->args);
		if (status != 0)
			set_exit_status(status);
	}
	else
	{
		status = execute_external(shell, all, curr);
		set_exit_status(status);
	}
	cleanup_redir(shell);
	return (status);
}

char	*find_full_path(char *cmd, char **paths)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, cmd);
		if (file_exist(full_path))
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	file_exist(char *path)
{
	if (!path)
		return (0);
	if (access(path, F_OK) == 0)
		return (1);
	return (0);
}

char	*find_cmd_path(char *cmd, t_env *env)
{
	char	*path;
	char	**paths;
	char	*full_path;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = get_env(env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	full_path = find_full_path(cmd, paths);
	free_str(paths);
	return (full_path);
}
