#include "minishell.h"

int	msg_error(t_env *env, char *msg, char *str, int status)
{
	write(2, msg, ft_strlen(msg));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	reset_status(env, status);
	return (status);
}

int	cmd_error(char	*cmd)
{
	write(2, "minishell$ ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	return (127);
}

int	fork_error(char	*cmd_path)
{
	perror("fork");
	free(cmd_path);
	return (1);
}
