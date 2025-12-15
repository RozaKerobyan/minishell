/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharteny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:32:37 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/11 18:32:39 by sharteny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_arg(char *arg, char **env, int code)
{
	char	*tmp;
	char	*quoted;

	tmp = expand_arg(arg, env, code);
	if (!tmp)
		return (NULL);
	quoted = rm_quotes(tmp);
	free(tmp);
	return (quoted);
}

int	handle_quote(char c, char *q, char *s, t_expander *e)
{
	if ((c == '\'' || c == '\"') && !*q)
	{
		if (ft_strchr(&s[e->i + 1], c))
			*q = c;
		else
			e->res[e->j++] = s[e->i];
		e->i++;
		return (1);
	}
	if (c == *q)
	{
		*q = 0;
		e->i++;
		return (1);
	}
	return (0);
}

char	*rm_quotes(char *s)
{
	t_expander	e;

	e.res = malloc(ft_strlen(s) + 1);
	if (!e.res)
		return (NULL);
	e.i = 0;
	e.j = 0;
	e.q = 0;
	while (s[e.i])
	{
		if (!handle_quote(s[e.i], &e.q, s, &e))
			e.res[e.j++] = s[e.i++];
	}
	e.res[e.j] = '\0';
	return (e.res);
}
