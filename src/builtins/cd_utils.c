#include "minishell.h"

char	*home_path(t_mini *shell)
{
	char	*cwd;
	char	**split;
	char	*home;
	char	*res;

	home = check_env_value(shell, "HOME");
	if (home)
		return (ft_strdup(home));
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	split = ft_split(cwd, '/');
	free(cwd);
	if (!split || !split[0] || !split[1])
		return (free_str(split), NULL);
	res = ft_strjoin("/", split[0]);
	res = ft_strjoin_free(res, "/");
	res = ft_strjoin_free(res, split[1]);
	free_str(split);
	return (res);
}

int	check_home(t_mini *shell, char **args)
{
	char	*home;

	home = check_env_value(shell, "HOME");
	if (!home && !args[1])
		return (msg_error(shell->env, "minishell$ cd: HOME not set", NULL, 1));
	return (0);
}

int	chdir_error(t_mini *shell, char *home, char *go)
{
	char	*error;

	error = strerror(errno);
	free_two(home, go);
	return (msg_error(shell->env, "minishell$ ", error, 1));
}

char	*cd_display(char *str)
{
	char	*dst;

	if (!str)
		return (NULL);
	dst = ft_strdup(str);
	if (!dst)
		return (NULL);
	if (dst[0] != '\0')
	{
		ft_putstr_fd(dst, 2);
		ft_putstr_fd("\n", 2);
	}
	return (dst);
}

int	cd_change(t_mini *shell, char **args)
{
	char	*home;
	char	*go;

	if (args[1] && args[2])
		return (msg_error(shell->env,
				"minishell$ cd: too many arguments", "", 1));
	if (check_home(shell, args))
		return (1);
	home = home_path(shell);
	if (!home)
		return (msg_error(shell->env,
				"minishell$ cd: cannot resolve HOME", NULL, 1));
	if (!args[1])
		go = ft_strdup(home);
	else if (!ft_strcmp(args[1], "-"))
		go = cd_display(check_env_value(shell, "OLDPWD"));
	else
		go = ft_strdup(args[1]);
	if (!go)
		return (free(home), msg_error(shell->env,
				"minishell$ cd: alloc error", NULL, 1));
	if (chdir(go) == -1)
		return (chdir_error(shell, home, go));
	free_two(home, go);
	return (0);
}
