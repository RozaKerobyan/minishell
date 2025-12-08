#include "minishell.h"

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../libft/libft.h"
#include <string.h>
*/

int	pwd_builtin(t_mini *shell, char **args)
{
	char	*directory;

	if (args && ft_strcmp(args[0], "pwd") == 0) // libt function add
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

/*
int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "pwd") == 0)
        pwd_builtin(&argv[1]);
    else
        return (0);
    return 0;
}
*/
