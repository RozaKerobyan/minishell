/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:24:02 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/15 02:24:03 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	history_capacity(t_mini *shell)
{
	char	**new;
	int		cap;

	if (shell->history_count + 1 < shell->history_capacity)
		return ;
	cap = shell->history_capacity * 2;
	new = malloc(sizeof(char *) * cap);
	if (!new)
		return ;
	ft_memcpy(new, shell->history,
		sizeof(char *) * shell->history_count);
	free(shell->history);
	shell->history = new;
	shell->history_capacity = cap;
}

void	add_shell_history(t_mini *shell, const char *line)
{
	if (!shell || !line || line[0] == '\0')
		return ;
	if (!shell->history)
	{
		shell->history_capacity = 16;
		shell->history = malloc(sizeof(char *)
				* shell->history_capacity);
		if (!shell->history)
			return ;
		shell->history_count = 0;
	}
	history_capacity(shell);
	shell->history[shell->history_count] = ft_strdup(line);
	if (shell->history[shell->history_count])
		shell->history_count++;
	shell->history[shell->history_count] = NULL;
}

int	history_builtin(t_mini *shell, char **args)
{
	int	i;

	(void)args;
	if (!shell || !shell->history)
		return (0);
	i = 0;
	while (i < shell->history_count && shell->history[i])
	{
		printf("%d  %s\n", i + 1, shell->history[i]);
		i++;
	}
	return (0);
}
