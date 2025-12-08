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
		if (str[i] == '\0')
			return (2);
	}
	return (0);
}

char	**add_variable(char **env, char *var)
{
	int		len;
	int		i;
	char	**env_mem;

	len = 0;
	while (env[len])
		len++;
	env_mem = malloc(sizeof(char *) * (len + 2));
	if (!env_mem)
		return (NULL);
	i = 0;
	while (i < len)
	{
		env_mem[i] = ft_strdup(env[i]);
		i++;
	}
	env_mem[len] = ft_strdup(var);
	env_mem[len + 1] = NULL;
	tab_free(env);
	return (env_mem);
}

int	find_var_index(char **env, char *var)
{
	int		i;
	char	*sign;

	i = 0;
	sign = ft_strjoin(var, "=");
	if (!sign)
		return (-1);
	while (env[i])
	{
		if (ft_strncmp(sign, env[i], ft_strlen(sign)) == 0)
		{
			free(sign);
			return (i);
		}
		i++;
	}
	free(sign);
	return (-1);
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
