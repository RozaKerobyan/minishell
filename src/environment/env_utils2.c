/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:24:30 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/15 02:24:32 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_child(char	*env)
{
	t_env	*new;
	char	*equal;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	equal = ft_strchr(env, '=');
	if (equal)
	{
		new->key = ft_substr(env, 0, equal - env);
		new->value = ft_strdup(equal + 1);
		new->flag = 1;
	}
	else
	{
		new->key = ft_strdup(env);
		new->value = ft_strdup("");
		new->flag = 0;
	}
	new->next = NULL;
	return (new);
}

t_env	*env_list_from_array(char **env)
{
	int		i;
	t_env	*list;
	t_env	*new;
	t_env	*last;

	i = 0;
	list = NULL;
	while (env && env[i])
	{
		new = create_env_child(env[i]);
		if (!new)
			return (NULL);
		if (!list)
			list = new;
		else
		{
			last = list;
			while (last->next)
				last = last->next;
			last->next = new;
		}
		i++;
	}
	return (list);
}

char	*env_str(t_env *child)
{
	char	*str;
	char	*tmp;

	if (child->flag != 0)
	{
		tmp = ft_strjoin(child->key, "=");
		str = ft_strjoin(tmp, child->value);
		free(tmp);
	}
	else
	{
		str = ft_strdup(child->key);
	}
	return (str);
}

char	**env_array_from_list(t_env *env)
{
	t_env	*tmp;
	char	**arr;
	int		count;
	int		i;

	tmp = env;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		arr[i] = env_str(tmp);
		i++;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}

char	*get_env(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
