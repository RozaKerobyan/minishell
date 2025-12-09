#include "minishell.h"

void	declare_x(char	**env)
{
	char	**sorted_env;

	sorted_env = sorted_copy(env);
	if (!sorted_env)
		return ;
	print_sorted_env(sorted_env);
	tab_free(sorted_env);
}

char	**export_remove(char **env, char **args, int i, int found)
{
	char	*var;

	var = ft_substr(args[i], 0, found);
	env = remove_var(env, var);
	free(var);
	return (env);
}

char	**export_update(char **env, char **args)
{
	int	i;
	int	found;
	int	del;

	i = 1;
	while (args[i])
	{
		found = 0;
		if (equal_sign(args[i], &found) == 0)
		{
			i++;
			continue ;
		}
		if (found > 0)
		{
			del = find_del_var(env, args, i, found);
			(void)del;
		}
		i++;
	}
	return (env);
}

void	handle_export_args(char **args, char ***env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!validation(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("`: not a valid identifier\n", 2);
			set_exit_status(1);
			i++;
			continue ;
		}
		if (ft_strchr(args[i], '='))
			*env = add_variable(*env, args[i]);
		i++;
	}
}

char	**export_builtin(char **env, char **args)
{
	set_exit_status(0);
	if (!args[1])
	{
		declare_x(env);
		return (env);
	}
	env = export_update(env, args);
	handle_export_args(args, &env);
	return (env);
}
