#include "minishell.h"

void	free_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
	{
		next = cmd->next;
		free_args(cmd->args);
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		if (cmd->heredoc_limiter)
			free(cmd->heredoc_limiter);
		free(cmd);
		cmd = next;
	}
}

void    free_shell_history(t_mini *shell)
{
    int i;

    if (!shell || !shell->history)
        return ;
    i = 0;
    while (i < shell->history_count)
    {
        free(shell->history[i]);
        i++;
    }
    free(shell->history);
    shell->history = NULL;
    shell->history_count = 0;
    shell->history_capacity = 0;
}

