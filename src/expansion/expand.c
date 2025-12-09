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

char	*rm_quotes(char *s)
{
	char		*res;
	t_expander	e;

	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	e.i = 0;
	e.j = 0;
	e.q = 0;
	e.res = res;
	while (s[e.i])
	{
		if ((s[e.i] == '\'' || s[e.i] == '\"') && !e.q)
		{
			if (ft_strchr(&s[e.i + 1], s[e.i]) != NULL)
				e.q = s[e.i++];
   			else
				res[e.j++] = s[e.i++];
		}
		else if (s[e.i] == e.q)
		{
			e.q = 0;
			e.i++;
		}
		else
			res[e.j++] = s[e.i++];
	}
	res[e.j] = '\0';
	return (res);
}

char	*expand_arg(char *arg, char **env, int code)
{
	char		*res;
	t_expander	e;

	res = malloc(4096);
	if (!res)
		return (NULL);
	e.i = 0;
	e.j = 0;
	e.q = 0;
	e.res = res;

	while (arg[e.i])
	{
		if ((arg[e.i] == '\'' || arg[e.i] == '\"') && !e.q)
			e.q = arg[e.i++];
		else if (arg[e.i] == e.q)
		{
			e.q = 0;
			e.i++;
		}
		else if (arg[e.i] == '$' && e.q != '\'')
			expand_dollar(arg, env, code, &e);
		else
			res[e.j++] = arg[e.i++];
	}
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
	char	*quoted;

	count = 0;
	while (args && args[count])
		count++;
	new = malloc(sizeof(char *) * (count + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < count)
	{
		tmp = expand_arg(args[i], env, code);
		quoted = rm_quotes(tmp);
		free(tmp);
		if (!quoted)
		{
			while (--i >= 0)
				free(new[i]);
			free(new);
			return (NULL);
		}
		new[i] = quoted;
		i++;
	}
	new[count] = NULL;
	return (new);
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
