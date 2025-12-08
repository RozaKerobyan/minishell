#include "minishell.h"

int	g_status = 0;

void	init_minishell(t_mini *shell, char **env)
{
	shell->env = env_list_from_array(env);
	shell->env_arr = env_array_from_list(shell->env);
	shell->input = -1;
	shell->output = -1;
	shell->status = 0;
	shell->cmd = NULL;
	shell->pid = -1;
	init_shlvl(shell);
	setup_signals();
}

int	main_loop(t_mini *shell)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
        	if (!line)
        	{
            		printf("exit\n");
            		break;
        	}

		if (line[0])
		{
			process_input(shell, line);
		}
		free(line);
        	if (g_status == SIGINT)
        		g_status = 0;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_mini *shell;

	(void)argc;
	(void)argv;

	shell = malloc(sizeof(t_mini));
	if (!shell)
	{
		perror("minishell");
		return (1);
	}
	init_minishell(shell, env);
	main_loop(shell);
	cleanup_minishell(shell);
	return (get_exit_status());
}
