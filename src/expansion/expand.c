/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharteny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:33:32 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/04 12:33:34 by sharteny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_expand_char(t_expander *e, char **env, int code, char *arg)
{
	char	c;

	c = arg[e->i];
	if ((c == '\'' || c == '\"') && !e->q)
	{
		e->q = c;
		e->i++;
	}
	else if (c == e->q)
	{
		e->q = 0;
		e->i++;
	}
	else if (c == '$' && e->q != '\'')
		expand_dollar(arg, env, code, e);
	else
		e->res[e->j++] = arg[e->i++];
}

char	*expand_arg(char *arg, char **env, int code)
{
	t_expander	e;
	char		*res;

	res = malloc(4096);
	if (!res)
		return (NULL);
	e.i = 0;
	e.j = 0;
	e.q = 0;
	e.res = res;
	while (arg[e.i])
		handle_expand_char(&e, env, code, arg);
	res[e.j] = '\0';
	return (res);
}

void	expand_dollar(char *arg, char **env, int code, t_expander *e)
{
	char	*tmp;

	if (arg[e->i] == '$')
		e->i++;
	if (arg[e->i] == '?')
	{
		tmp = exit_code_str(code);
		e->j = copy_var(e->res, e->j, tmp);
		free(tmp);
		e->i++;
	}
	else if (!is_var_char(arg[e->i]))
	{
		e->res[e->j++] = '$';
	}
	else
		expand_variable(arg, env, e);
}

char	**expand_args(char **args, char **env, int code)
{
	int		count;
	int		i;
	char	**new;
	char	*tmp;

	count = 0;
	while (args && args[count])
		count++;
	new = malloc(sizeof(char *) * (count + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < count)
	{
		tmp = process_arg(args[i], env, code);
		if (!tmp)
		{
			free_args_array(new, i);
			return (NULL);
		}
		new[i] = tmp;
		i++;
	}
	new[count] = NULL;
	return (new);
}
