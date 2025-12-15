/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 02:27:04 by rkerobya          #+#    #+#             */
/*   Updated: 2025/12/15 02:27:06 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	atoi_check_overflow(unsigned long long num, int sign, int *err)
{
	if (sign == 1 && num > LONG_MAX)
	{
		*err = 1;
		return (1);
	}
	if (sign == -1 && num > (unsigned long long)LONG_MAX + 1)
	{
		*err = 1;
		return (1);
	}
	return (0);
}

long	ft_atoi_long(const char *str, int *err_status)
{
	unsigned long long	num;
	int					i;
	int					sign;

	i = 0;
	sign = 1;
	num = 0;
	if (err_status)
		*err_status = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - '0');
		if (atoi_check_overflow(num, sign, err_status))
			return (0);
		i++;
	}
	return (sign * (long)num);
}
