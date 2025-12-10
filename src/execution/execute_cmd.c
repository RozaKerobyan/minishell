#include "minishell.h"

int execute_cmd(t_mini *shell, t_cmd *all, t_cmd *curr)
{
	int	status;
	int	redir_result;

	if (!curr->args || !curr->args[0])
		return (0);
	redir_result = setup_redir(shell, curr);
	if (redir_result == -2)
	{
		return (1);
	}
	if (redir_result == -1)
	{
		set_exit_status(1);
        	return (1);
	}
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
