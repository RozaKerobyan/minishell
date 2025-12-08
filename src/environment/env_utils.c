#include "minishell.h"

char    *check_env_value(t_mini *shell, char *key)
{
        t_env *tmp;

        tmp = shell->env;
        while (tmp)
        {
                if (!ft_strcmp(tmp->key, key))
                        return (tmp->value);
                tmp = tmp->next;
        }
        return (NULL);
}

int	reset_status(t_env *env, int status)
{
	char	*new;
	t_env	*tmp;

	tmp = env;
	errno = status;
	new = ft_itoa(status);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "?"))
		{
			free(tmp->value);
			tmp->value = new;
			return (status);
		}
		tmp = tmp->next;
	}
	free(new);
	return (-1);
}

t_env	*env_child(t_mini *shell, char *key)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void    env_change(t_env *env, char *key, char *s, int n)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(s);
			tmp->flag = n;
			return ;
		}
		tmp = tmp->next;
	}
}

void	env_add_if_missing(t_mini *shell, char *key, char *value, int flag)
{
	t_env	*new_env;
	t_env	*tmp;

	if (env_child(shell, key))
		return ;
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return ;
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->flag = flag;
	new_env->next = NULL;
	if (!shell->env)
	{
		shell->env = new_env;
		return ;
	}
	tmp = shell->env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_env;
}
