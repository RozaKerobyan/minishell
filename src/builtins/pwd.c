#include "minishell.h"

int	pwd_builtin(t_mini *shell, char **args)
{
	char	*directory;

	if (args && ft_strcmp(args[0], "pwd") == 0)
	{
		directory = getcwd(NULL, 0);
		if (directory)
		{
			printf("%s\n", directory);
			free(directory);
		}
		else
			ft_putstr_fd("Error: Could not get the current directory\n", 2);
		reset_status(shell->env, 0);
		return (0);
	}
	return (1);
}
