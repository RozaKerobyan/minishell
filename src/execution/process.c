#include "minishell.h"

int	process_status(int status)
{
	if (status == 0)
		return (0);
	if (status == 256)
		return (1);
	if (status == 512)
		return (2);
	if (status == 32512)
		return (127);
	return (status);
}

int	setup_child_redir(t_mini *shell, t_cmd *all, t_cmd *curr)
{
	if (!set_pipe_fds(all, curr))
		return (0);
	if (redirections(shell) == -1)
		return (0);
	return (1);
}

void	child_cmd(t_mini *shell, t_cmd *curr)
{
	char	*cmd_path;

	if (builtins(curr->args[0]))
		exit(execute_builtins(shell, curr->args));
	cmd_path = find_cmd_path(curr->args[0], shell->env);
	if (!cmd_path)
	{
		write(2, "minishell: ", 11);
		write(2, curr->args[0], ft_strlen(curr->args[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	execve(cmd_path, curr->args, shell->env_arr);
	perror("minishell");
	free(cmd_path);
	exit(127);
}

void	child_process(t_mini *shell, t_cmd *all, t_cmd *curr)
{
	if (!setup_child_redir(shell, all, curr))
		exit(1);
	setup_signals_child();
	if (curr->args && curr->args[0])
		child_cmd(shell, curr);
	exit(0);
}

int execute_external(t_mini *shell, t_cmd *all, t_cmd *curr)
{
	char *cmd_path;
	pid_t pid;
	int status;

	cmd_path = find_cmd_path(curr->args[0], shell->env);
	if (!cmd_path)
		return (cmd_error(curr->args[0]));
	setup_signals_parent_exec();
	pid = fork();
	if (pid == -1)
	{
		setup_signals(); 
		return (fork_error(cmd_path));
	}
	if (pid == 0)
	{
		setup_signals_child();
		child_process(shell, all, curr);
	}
	curr->pid = pid;
	setup_signals();
	waitpid(pid, &status, 0);
	free(cmd_path);
	return (process_status(status));
}
