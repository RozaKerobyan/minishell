/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:23:40 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/20 18:38:46 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validation(char	*str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] && (ft_isalpha(str[0]) || str[0] == '_'))
	{
		i = 1;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		{
			i++;
		}
		if (str[i] == '=')
			return (1);
		if (str[i] == '+' && str[i + 1] == '=')
			return (3);
		if (str[i] == '\0')
			return (2);
	}
	return (0);
}

char	**add_variable(char **env, char *var)
{
	int	index;

	index = find_var_index(env, var);
	if (index != -1)
		return (replace_variable(env, var, index));
	return (append_variable(env, var));
}

char	**remove_var(char **env, char *var)
{
	int	index;
	int	len;
	int	i;

	len = 0;
	index = find_var_index(env, var);
	if (index == -1)
		return (env);
	while (env[len])
		len++;
	i = index;
	while (i < len - 1)
	{
		free(env[i]);
		env[i] = ft_strdup(env[i + 1]);
		i++;
	}
	free(env[len - 1]);
	env[len - 1] = NULL;
	return (env);
}

int	equal_sign(char	*str, int *found)
{
	int	i;

	i = 0;
	*found = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			*found = 1;
		}
		i++;
	}
	return (*found);
}

void	handle_one_export(char *arg, char ***env)
{
	int	valid;
	int	index;

	if (!export_validation(arg))
		return ;
	valid = validation(arg);
	if (valid == 1)
		*env = add_variable(*env, arg);
	else if (valid == 3)
		handle_append_variable(env, arg);
	else if (valid == 2)
	{
		index = find_var_index(*env, arg);
		if (index == -1)
			*env = add_variable(*env, arg);
	}
}
