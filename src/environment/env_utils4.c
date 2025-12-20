/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 18:32:38 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/20 18:33:34 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**replace_variable(char **env, char *var, int index)
{
	free(env[index]);
	env[index] = ft_strdup(var);
	return (env);
}

char	**append_variable(char **env, char *var)
{
	int		len;
	int		i;
	char	**new_env;

	len = 0;
	while (env[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[len] = ft_strdup(var);
	new_env[len + 1] = NULL;
	tab_free(env);
	return (new_env);
}
