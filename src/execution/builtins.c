#include "minishell.h"

int	builtins(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "history") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
                return (1);
	if (ft_strcmp(cmd, "cd") == 0)
                return (1);
	if (ft_strcmp(cmd, "unset") == 0)
                return (1);
	if (ft_strcmp(cmd, "exit") == 0)
                return (1);
	if (ft_strcmp(cmd, "env") == 0)
                return (1);
	if (ft_strcmp(cmd, "export") == 0)
                return (1);
	return (0);
}

int	execute_builtins(t_mini *shell, char **args)
{
	int	status = 0;
	int	stdout_backup = -1;
	int	stdin_backup = -1;
	
	if (shell->input != -1)
	{
		stdin_backup = dup(STDIN_FILENO);
		dup2(shell->input, STDIN_FILENO);
	}
	if (shell->output != -1)
	{
		stdout_backup = dup(STDOUT_FILENO);
		dup2(shell->output, STDOUT_FILENO);
	}
	if (ft_strcmp(args[0], "echo") == 0)
		status = echo_builtin(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		status = pwd_builtin(shell, args);
	else if (ft_strcmp(args[0], "cd") == 0)
		status = cd_builtin(shell, args);
	else if (ft_strcmp(args[0], "unset") == 0)
	{
		unset_builtin(shell, args);
		status = get_exit_status();
	}
	else if (ft_strcmp(args[0], "exit") == 0)
		status = exit_builtin(shell, args);
	else if (ft_strcmp(args[0], "env") == 0)
		status = env_builtin(shell);
	else if (ft_strcmp(args[0], "export") == 0)
	{
		shell->env_arr = export_builtin(shell->env_arr, args);
		shell->env = env_list_from_array(shell->env_arr);
		status = get_exit_status();
	}
	else if (ft_strcmp(args[0], "history") == 0)
		status = history_builtin(shell, args);
	if (stdin_backup != -1)
	{
		dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
	}
	if (stdout_backup != -1)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
	}
	return (status);
}

int     file_exist(char *path)
{
	if (!path)
		return (0);
	if (access(path, F_OK) == 0)
		return (1);
	return (0);
}

char    *find_cmd_path(char *cmd, t_env *env)
{
        char    *path;
        char    **paths;
        char    *full_path;
        int     i;

        if (!cmd || cmd[0] == '\0')
                return (NULL);
        if (ft_strchr(cmd, '/') != NULL)
        {
                if (file_exist(cmd))
                        return (ft_strdup(cmd));
                return (NULL);
        }
        path = get_env(env, "PATH");
        if (!path)
                return (NULL);
        paths = ft_split(path, ':');
        i = 0;
        while (paths && paths[i])
        {
                full_path = ft_strjoin(paths[i], "/");
                full_path = ft_strjoin_free(full_path, cmd);
                if (file_exist(full_path))
                {
                        free_str(paths);
                        return (full_path);
                }
                free(full_path);
                i++;
        }
        free_str(paths);
        return (NULL);
}
