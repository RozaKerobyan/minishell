/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:24:13 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/20 02:19:22 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validation_unset(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	if (ft_isdigit(str[0]))
		return (0);
	i = 0;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

t_env	*remove_env_var(t_env *env, char *var)
{
	t_env	*prev;
	t_env	*curr;

	if (!env || !var)
		return (env);
	curr = env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, var) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return (env);
		}
		prev = curr;
		curr = curr->next;
	}
	return (env);
}

void	unset_builtin(t_mini *shell, char **args)
{
	int	i;

	set_exit_status(0);
	if (!args[1])
		return ;
	i = 1;
	while (args[i])
	{
		if (validation_unset(args[i]))
		{
			shell->env = remove_env_var(shell->env, args[i]);
			shell->env_arr = remove_var(shell->env_arr, args[i]);
		}
		i++;
	}
}
