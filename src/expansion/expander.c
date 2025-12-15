/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharteny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:33:44 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/04 12:33:46 by sharteny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_variable(char *arg, char **env, t_expander *e)
{
	int		start;
	int		len;
	char	*name;
	char	*val;

	start = e->i;
	while (is_var_char(arg[e->i]))
		e->i++;
	len = e->i - start;
	if (len > 0)
	{
		name = substr(arg, start, len);
		val = env_val(name, env);
		e->j = copy_var(e->res, e->j, val);
		free(name);
	}
}

void	expander(t_cmd *cmd, char **env, int code)
{
	char	**new;
	char	**old;

	if (!cmd || !env)
		return ;
	while (cmd)
	{
		if (cmd->args)
		{
			old = cmd->args;
			new = expand_args(cmd->args, env, code);
			if (new)
			{
				cmd->args = new;
				free_old_args(old);
			}
		}
		cmd = cmd->next;
	}
}

void	execute_expander(t_cmd *cmd, char **env, int code, t_mini *shell)
{
	if (!cmd)
		return ;
	if (!env && shell)
		env = shell->env_arr;
	if (!env)
		return ;
	expander(cmd, env, code);
}

int	free_old_args(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	return (0);
}
