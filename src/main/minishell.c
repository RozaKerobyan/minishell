/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:00:51 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/20 22:55:45 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	init_minishell(t_mini *shell, char **env)
{
	shell->env = env_list_from_array(env);
	shell->env_arr = env_array_from_list(shell->env);
	shell->input = -1;
	shell->output = -1;
	shell->status = 0;
	shell->cmd = NULL;
	shell->pid = -1;
	shell->history = NULL;
	shell->history_count = 0;
	shell->history_capacity = 0;
	init_shlvl(shell);
	setup_signals();
}

int	main_loop(t_mini *shell)
{
	char	*line;

	while (1)
	{
		line = readline("\001\033[1;92m\002minishell$ \001\033[0m\002");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (line[0])
			process_input(shell, line);
		free(line);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	*shell;

	if (argc != 1)
	{
		ft_putstr_fd("no arguments allowed\n", 2);
		return (1);
	}
	(void)argv;
	shell = malloc(sizeof(t_mini));
	if (!shell)
	{
		perror("minishell");
		return (1);
	}
	init_minishell(shell, env);
	main_loop(shell);
	cleanup_minishell(shell);
	return (get_exit_status());
}
