#include "minishell.h"

// 25 more line
int	status_exit(char *arg, int *err_status)
{
	int	i;

	i = 0;
	if (!arg)
		return (get_exit_status());
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
	{
		*err_status = 1;
		return (0);
	}
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
	{
		*err_status = 1;
		return (0);
	}
	while (arg[i]) 
	{
		if (!ft_isdigit(arg[i]) && !ft_isspace(arg[i]))
		{
			*err_status = 1;
			return (0);
		}
		i++;
	}
	return (ft_atoi_long(arg, err_status) % 256);
}

bool	quiet_mode(t_mini *shell)
{
	t_cmd *cmd;

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

// 25 more line
int	exit_builtin(t_mini *shell, char **args)
{
	int		err_status;
	int		exit_code;
	bool	quiet_status;

	err_status = 0;
	quiet_status = quiet_mode(shell);
	if (!quiet_status && shell->input)
		write(2, "exit\n", 5);
	if (!args || !args[1])
	{
		exit_code = get_exit_status();
	}
	else
	{
		exit_code = status_exit(args[1], &err_status);
		if (err_status)
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			exit_code = 2;
		}
		else if (args[2])
		{
			printf("exit: too many arguments\n");
			return (1);
		}
	}
	
	exit_shell(shell, exit_code);
	return (2);
}
