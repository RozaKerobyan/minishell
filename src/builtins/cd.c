/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:22:46 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/15 02:22:48 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_cd_env(t_mini *shell, char *oldpwd, char *pwd)
{
	t_env	*oldpwd_k;
	t_env	*pwd_k;

	if (!shell)
		return ;
	oldpwd_k = env_child(shell, "OLDPWD");
	pwd_k = env_child(shell, "PWD");
	if (!pwd_k)
	{
		if (!oldpwd_k || oldpwd_k->flag == 0)
			return ;
		else
			env_change(shell->env, "OLDPWD", " ", 1);
	}
	else
	{
		if (pwd)
			env_change(shell->env, "PWD", pwd, 1);
		if (oldpwd && oldpwd_k)
			env_change(shell->env, "OLDPWD", oldpwd, 1);
	}
}

void	oldpwd_and_pwd(t_env *env, char **pwd, char **oldpwd)
{
	t_env	*tmp;

	tmp = env;
	if (*pwd || *oldpwd)
		return ;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
		{
			*pwd = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			*oldpwd = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
}

int	cd_builtin(t_mini *shell, char **args)
{
	char	*pwd;
	char	*oldpwd;
	int		status;

	pwd = NULL;
	oldpwd = getcwd(NULL, 0);
	status = cd_change(shell, args);
	if (status == 0)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			oldpwd_and_pwd(shell->env, &pwd, &oldpwd);
		change_cd_env(shell, oldpwd, pwd);
	}
	free(pwd);
	free(oldpwd);
	reset_status(shell->env, status);
	return (status);
}
