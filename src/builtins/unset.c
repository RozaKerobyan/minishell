#include "minishell.h"

int	validation_unset(char *str)
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
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

char	**unset_builtin(char **env, char **args)
{
	int	i;

	set_exit_status(0);  
	if (!args[1])
		return (env);
	i = 1;
	while (args[i])
	{
		if (!validation(args[i]))
		{
			printf("unset: %s: invalid parameter name\n", args[i]);
			set_exit_status(1);
			i++;
			continue ;
		}
		env = remove_var(env, args[i]);
		i++;
	}
	return (env);
}
