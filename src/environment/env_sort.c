#include "minishell.h"

void	sort_env_arr(char **env, int count)
{
	int	i;
	int	j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**sorted_copy(char **env)
{
	int	count;
	int	i;
	char	**sorted_env;

	count = 0;
	while (env[count])
		count++;
	sorted_env = malloc(sizeof(char *) * (count + 1));
	if (!sorted_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		sorted_env[i] = ft_strdup(env[i]);
		i++;
	}
	sorted_env[count] = NULL;
	sort_env_arr(sorted_env, count);
	return (sorted_env);
}

void	print_env_var(char *var)
{
	char	*equal;
	char	*start;
	
	equal = ft_strchr(var, '=');
	if (equal)
	{
		start = equal + 1;
		if (start[0] == '"' && start[ft_strlen(start) - 1] == '"')
		{
			start[ft_strlen(start) - 1] = '\0';
			start++;
		}
		*equal = '\0';
		printf("declare -x %s=\"%s\"\n", var, start);
		*equal = '=';
	}
	else
	{
		printf("declare -x %s\n", var);
	}
}
void	print_sorted_env(char **sorted_env)
{
	int	i;

	i = 0;
	while (sorted_env[i])
	{
		if (ft_strncmp(sorted_env[i], "_=", 2) != 0)
			print_env_var(sorted_env[i]);
		i++;
	}
}
