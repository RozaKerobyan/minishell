/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:22:58 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/15 02:23:00 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
