/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:24:35 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/20 18:49:09 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_del_var(char **env, char **args, int i, int found)
{
	int	n;

	n = 0;
	while (env[n])
	{
		if (ft_strncmp(args[i], env[n], found + 1) == 0)
		{
			env = export_remove(env, args, i, found);
			return (1);
		}
		n++;
	}
	return (0);
}

void	update_env_both(t_mini *shell, char *key, char *value, int flag)
{
	char	*var;

	env_change(shell->env, key, value, flag);
	shell->env_arr = remove_var(shell->env_arr, key);
	var = ft_strjoin(key, "=");
	var = ft_strjoin_free(var, value);
	shell->env_arr = add_variable(shell->env_arr, var);
	free(var);
}

int	get_var_name_len(char *var)
{
	char	*equal_sign;
	char	*plus_sign;

	plus_sign = ft_strchr(var, '+');
	if (plus_sign && plus_sign[1] == '=')
		return (plus_sign - var);
	equal_sign = ft_strchr(var, '=');
	if (equal_sign)
		return (equal_sign - var);
	return (ft_strlen(var));
}

int	find_var_index(char **env, char *var)
{
	int		i;
	int		name_len;
	char	*var_name;

	name_len = get_var_name_len(var);
	var_name = ft_substr(var, 0, name_len);
	if (!var_name)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var_name, env[i], name_len) == 0
			&& (env[i][name_len] == '=' || env[i][name_len] == '\0'))
		{
			free(var_name);
			return (i);
		}
		i++;
	}
	free(var_name);
	return (-1);
}
