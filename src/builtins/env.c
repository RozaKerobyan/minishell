#include "minishell.h"

int	env_builtin(t_mini *shell)
{
	t_env	*current;

	if (!shell || !shell->env)
		return (1);
	current = shell->env;
	while (current)
	{
		if (current->value && current->flag != 0)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	reset_status(shell->env, 0);
	return (0);
}
