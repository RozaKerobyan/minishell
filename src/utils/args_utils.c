/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:26:42 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/15 02:26:44 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_redir_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (redir_type(args[i]) == 0)
		{
			if (i != j)
				args[j] = args[i];
			j++;
		}
		else
		{
			free(args[i]);
			if (args[i + 1])
			{
				free(args[i + 1]);
				i++;
			}
		}
		i++;
	}
	args[j] = NULL;
}

int	count_args_without_redir(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (redir_type(args[i]) == 0)
			count++;
		else if (args[i + 1])
			i++;
		i++;
	}
	return (count);
}
