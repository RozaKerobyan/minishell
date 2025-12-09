#include "minishell.h"

int	check_exit_num(char *arg, int *err_status, int *i)
{
	while (ft_isspace(arg[*i]))
		(*i)++;
	if (arg[*i] == '\0')
	{
		*err_status = 1;
		return (0);
	}
	if (arg[*i] == '-' || arg[*i] == '+')
		(*i)++;
	if (!ft_isdigit(arg[*i]))
	{
		*err_status = 1;
		return (0);
	}
	return (1);
}

int	status_exit(char *arg, int *err_status)
{
	int	i;

	i = 0;
	if (!arg)
		return (get_exit_status());
	if (!check_exit_num(arg, err_status, &i))
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && !ft_isspace(arg[i]))
		{
			*err_status = 1;
			return (0);
		}
		i++;
	}
	return (ft_atoi_long(arg, err_status) % 256);
}
