#include "minishell.h"

#include "minishell.h"

void	process_input(t_mini *shell, char *input)
{
	t_token	*tokens;
	t_cmd	*cmd;

	if (!input || input[0] == '\0')
		return ;
	add_history(input);
	add_shell_history(shell, input);
	tokens = tokenize_line(input);
	if (!tokens)
	{
		reset_status(shell->env, 2);
		return ;
	}
	cmd = parse_tokens(tokens);
	free_tokens(tokens);
	if (!cmd)
	{
		reset_status(shell->env, 2);
		return ;
	}
	shell->cmd = cmd;
	execute_expander(cmd, shell->env_arr, shell->status, shell);
	if (cmd->next)
		shell->status = execute_pipeline(shell, cmd);
	else
		shell->status = execute_cmd(shell, cmd, cmd);
	shell->cmd = NULL;
}
