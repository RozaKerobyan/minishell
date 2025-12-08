/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharteny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:33:53 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/04 12:33:56 by sharteny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_char(char c)
{
	if (c == '_' || (c >= 'A' && c <= 'Z'))
		return (1);
	if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

char	*env_val(char *name, char **env)
{
	int		i;
	int		len;

	len = strlen(name);
	i = 0;
	while (env && env[i])
	{
		if (!strncmp(env[i], name, len) && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return ("");
}

char	*exit_code_str(int code)
{
	char	buf[12];
	int		i;
	int		n;

	n = code;
	i = 10;
	buf[11] = '\0';
	if (n == 0)
		buf[i--] = '0';
	while (n > 0 && i >= 0)
	{
		buf[i--] = '0' + (n % 10);
		n /= 10;
	}
	return (strdup(buf + i + 1));
}

char	*substr(char *s, int start, int len)
{
	char	*res;
	int		i;

	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	copy_var(char *res, int j, char *val)
{
	int		k;

	k = 0;
	while (val && val[k])
	{
		res[j] = val[k];
		j++;
		k++;
	}
	return (j);
}
