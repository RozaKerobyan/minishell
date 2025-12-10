#include "minishell.h"

void	del_empty_args_cmd(t_cmd *cmd)
{
	t_cmd	*curr;
	int		i;
	int		j;
	int		keep;
	char	**new;

	curr = cmd;
	while (curr)
	{
		if (curr->args)
		{
			i = 0;
			keep = 0;
			while (curr->args[i])
			{
				if (curr->args[i][0] != '\0')
					keep++;
				i++;
			}
			if (keep == 0)
			{
				free_old_args(curr->args);
				curr->args = NULL;
			}
			else if (keep < i)
			{
				new = malloc(sizeof(char *) * (keep + 1));
				if (!new)
					continue;
				j = 0;
				i = 0;
				while (curr->args[i])
				{
					if (curr->args[i][0] != '\0')
						new[j++] = curr->args[i];
					else
						free(curr->args[i]);
					i++;
				}
				new[j] = NULL;
				free(curr->args);
				curr->args = new;
			}
		}
		curr = curr->next;
	}
}

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
	execute_expander(cmd, shell->env_arr, g_status, shell);
	del_empty_args_cmd(cmd);
	if (g_status == 130)
		g_status = 0;
	if (cmd->next)
		shell->status = execute_pipeline(shell, cmd);
	else
		shell->status = execute_cmd(shell, cmd, cmd);
	free_cmds(cmd);
	shell->cmd = NULL;
}
