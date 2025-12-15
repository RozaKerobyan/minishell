/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:50:00 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/15 02:10:34 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "history") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	return (0);
}

void	check_builtins(t_mini *shell, char **args, int *status)
{
	if (ft_strcmp(args[0], "echo") == 0)
		*status = echo_builtin(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		*status = pwd_builtin(shell, args);
	else if (ft_strcmp(args[0], "cd") == 0)
		*status = cd_builtin(shell, args);
	else if (ft_strcmp(args[0], "unset") == 0)
	{
		unset_builtin(shell, args);
		*status = get_exit_status();
	}
	else if (ft_strcmp(args[0], "exit") == 0)
		*status = exit_builtin(shell, args);
	else if (ft_strcmp(args[0], "env") == 0)
		*status = env_builtin(shell);
	else if (ft_strcmp(args[0], "export") == 0)
	{
		shell->env_arr = export_builtin(shell->env_arr, args);
		shell->env = env_list_from_array(shell->env_arr);
		*status = get_exit_status();
	}
	else if (ft_strcmp(args[0], "history") == 0)
		*status = history_builtin(shell, args);
}

void	restore_std_fd(int stdin_bak, int stdout_bak)
{
	if (stdin_bak != -1)
	{
		dup2(stdin_bak, STDIN_FILENO);
		close(stdin_bak);
	}
	if (stdout_bak != -1)
	{
		dup2(stdout_bak, STDOUT_FILENO);
		close(stdout_bak);
	}
}

int	execute_builtins(t_mini *shell, char **args)
{
	int	status;
	int	stdout_backup;
	int	stdin_backup;

	status = 0;
	stdin_backup = -1;
	stdout_backup = -1;
	if (shell->input != -1)
	{
		stdin_backup = dup(STDIN_FILENO);
		dup2(shell->input, STDIN_FILENO);
	}
	if (shell->output != -1)
	{
		stdout_backup = dup(STDOUT_FILENO);
		dup2(shell->output, STDOUT_FILENO);
	}
	check_builtins(shell, args, &status);
	restore_std_fd(stdin_backup, stdout_backup);
	return (status);
}

int	file_exist(char *path)
{
	if (!path)
		return (0);
	if (access(path, F_OK) == 0)
		return (1);
	return (0);
}
