/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:24:40 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/15 02:24:42 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_shlvl(t_mini *shell)
{
	char	*lvl_str;
	int		lvl;

	lvl_str = check_env_value(shell, "SHLVL");
	if (!lvl_str)
		return (1);
	lvl = ft_atoi(lvl_str);
	if (lvl < 0)
		return (0);
	return (lvl);
}

void	update_shlvl(t_mini *shell)
{
	char	*lvl_str;
	char	*new_lvl;
	int		cur_lvl;

	lvl_str = check_env_value(shell, "SHLVL");
	if (!lvl_str)
	{
		env_change(shell->env, "SHLVL", "1", 1);
		return ;
	}
	cur_lvl = ft_atoi(lvl_str);
	if (cur_lvl < 0)
		cur_lvl = 0;
	else
		cur_lvl++;
	new_lvl = ft_itoa(cur_lvl);
	env_change(shell->env, "SHLVL", new_lvl, 1);
	free(new_lvl);
}

void	init_shlvl(t_mini *shell)
{
	update_shlvl(shell);
}

void	check_large_lvl(t_mini *shell)
{
	char	*lvl_str;
	long	lvl;

	lvl_str = check_env_value(shell, "SHLVL");
	if (!lvl_str)
		return ;
	lvl = ft_atoi_long(lvl_str, NULL);
	if (lvl > 1000)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putstr_fd(lvl_str, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		env_change(shell->env, "SHLVL", "1", 1);
	}
}
