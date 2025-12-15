/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:00:51 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/15 02:26:26 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exit_status(void)
{
	return (g_status & EXIT_STATUS_MASK);
}

void	set_exit_status(int status)
{
	g_status = (g_status & ~EXIT_STATUS_MASK) | (status & EXIT_STATUS_MASK);
}
