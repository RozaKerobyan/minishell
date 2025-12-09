#include "minishell.h"

int	n_option(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] != '-')
		return (false);
	i++;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

void	echo_output(char **args, bool flag, int i)
{
	if (!args[i])
	{
		if (!flag)
			printf("\n");
		return ;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
}

int	echo_builtin(char **args)
{
	int		i;
	bool	flag;

	flag = false;
	i = 1;
	while (args[i] && n_option(args[i]))
	{
		flag = true;
		i++;
	}
	echo_output(args, flag, i);
	return (0);
}
