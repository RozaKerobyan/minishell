/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:22:49 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/20 18:40:17 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msg_error(t_env *env, char *msg, char *str, int status)
{
	if (ft_strncmp(msg, "cd: ", 4) == 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		if (str && *str)
		{
			ft_putstr_fd(str, STDERR_FILENO);
		}
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		if (str && *str)
		{
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
		}
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	if (env)
		reset_status(env, status);
	return (status);
}

void	minishell_error(char *cmd, char *msg)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	cmd_error(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == -1)
		{
			minishell_error(cmd, "No such file or directory");
			return (127);
		}
		else if (check_directory(cmd))
		{
			minishell_error(cmd, "Is a directory");
			return (126);
		}
		else if (access(cmd, X_OK) == -1)
		{
			minishell_error(cmd, "Permission denied");
			return (126);
		}
	}
	minishell_error(cmd, "command not found");
	return (127);
}

int	fork_error(char	*cmd_path)
{
	perror("fork");
	free(cmd_path);
	return (1);
}

int	export_validation(char *arg)
{
	if (!validation(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		set_exit_status(1);
		return (0);
	}
	return (1);
}
