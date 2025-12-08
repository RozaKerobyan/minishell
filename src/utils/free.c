#include "minishell.h"

void	tab_free(char	**tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if (!join)
	{
		free(s1);
		return (NULL);
	}
	free(s1);
	return (join);
}

char	**free_str(char **str)
{
	int i;

	i = -1;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		if (str[i])
			free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
	return (NULL);
}

int	free_two(char *first_str, char *second_str)
{
	if (first_str)
		free(first_str);
	if (second_str)
		free(second_str);
	return (0);
}

void	cleanup_redir(t_mini *shell)
{
	if (!shell)
		return ;
	close_fd(&(shell->input));
	close_fd(&(shell->output));
}

void	cleanup_minishell(t_mini *shell)
{
	if (!shell)
		return ;
	if (shell->env)
		free_env(shell->env);
	if (shell->env_arr)
		free_str(shell->env_arr);
	if (shell->cmd)
		free_cmds(shell->cmd);
	cleanup_redir(shell);
	free(shell);
}
