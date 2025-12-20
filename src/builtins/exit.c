/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:23:08 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/19 23:05:16 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	quiet_mode(t_mini *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	if (cmd && (cmd->next || cmd->prev))
		return (true);
	return (false);
}

void	exit_shell(t_mini *shell, int exit_mode)
{
	if (shell)
	{
		if (shell->cmd)
			cleanup_redir(shell);
		cleanup_minishell(shell);
	}
	exit(exit_mode);
}

void	print_exit_num_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	handle_exit_args(char **args, int *exit_code)
{
	int	err_status;

	err_status = 0;
	if (!args || !args[1])
	{
		*exit_code = get_exit_status();
		return (0);
	}
	*exit_code = status_exit(args[1], &err_status);
	if (err_status)
	{
		print_exit_num_error(args[1]);
		*exit_code = 2;
		return (0);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	exit_builtin(t_mini *shell, char **args)
{
	int		exit_code;
	bool	quiet_status;

	quiet_status = quiet_mode(shell);
	if (!quiet_status && shell->input)
		write(2, "exit\n", 5);
	if (handle_exit_args(args, &exit_code))
		return (1);
	exit_shell(shell, exit_code);
	return (2);
}
