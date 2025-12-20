/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 18:43:49 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/20 18:50:40 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_append(char *arg, char **name, char **value)
{
	char	*plus;

	plus = ft_strchr(arg, '+');
	if (!plus || plus[1] != '=')
		return (0);
	*name = ft_substr(arg, 0, plus - arg);
	*value = ft_strdup(plus + 2);
	return (*name && *value);
}

char	*make_var(char *name, char *value)
{
	char	*tmp;

	tmp = ft_strjoin(name, "=");
	return (ft_strjoin_free(tmp, value));
}

void	append_existing(char ***env, int index, char *add_val, char *var_name)
{
	char	*equal;
	char	*current_value;
	char	*new_value;
	char	*new_var;

	equal = ft_strchr((*env)[index], '=');
	if (equal)
		current_value = ft_strdup(equal + 1);
	else
		current_value = ft_strdup("");
	new_value = ft_strjoin(current_value, add_val);
	free(current_value);
	new_var = make_var(var_name, new_value);
	free((*env)[index]);
	(*env)[index] = new_var;
	free(new_value);
}

void	append_new(char ***env, char *name, char *value)
{
	char	*new_var;

	new_var = make_var(name, value);
	*env = add_variable(*env, new_var);
	free(new_var);
}

void	handle_append_variable(char ***env, char *arg)
{
	char	*name;
	char	*value;
	int		index;

	if (!parse_append(arg, &name, &value))
		return ;
	index = find_var_index(*env, name);
	if (index == -1)
		append_new(env, name, value);
	else
		append_existing(env, index, value, name);
	free(name);
	free(value);
}
