/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:24:35 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/15 02:24:36 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_del_var(char **env, char **args, int i, int found)
{
	int	n;

	n = 0;
	while (env[n])
	{
		if (ft_strncmp(args[i], env[n], found + 1) == 0)
		{
			env = export_remove(env, args, i, found);
			return (1);
		}
		n++;
	}
	return (0);
}
