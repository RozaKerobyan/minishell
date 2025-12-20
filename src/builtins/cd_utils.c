/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:23:03 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/20 18:19:12 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (msg_error(shell->env, "cd: HOME not set", "", 1));
	return (0);
}

int	chdir_error(char *path)
{
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(path);
		return (1);
	}
	free(path);
	return (0);
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
		ft_putstr_fd(dst, 1);
		ft_putstr_fd("\n", 1);
	}
	return (dst);
}

char	*cd_target(t_mini *shell, char **args)
{
	char	*home;

	if (args[1] && args[2])
	{
		msg_error(shell->env, "cd: too many arguments", "", 1);
		return (NULL);
	}
	if (check_home(shell, args))
		return (NULL);
	home = home_path(shell);
	if (!home)
	{
		msg_error(shell->env, "cd: cannot resolve HOME", NULL, 1);
		return (NULL);
	}
	if (!args[1])
		return (home);
	if (!ft_strcmp(args[1], "-"))
	{
		free(home);
		return (cd_display(check_env_value(shell, "OLDPWD")));
	}
	free(home);
	return (ft_strdup(args[1]));
}
