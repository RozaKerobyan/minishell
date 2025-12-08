#include "minishell.h"

long	ft_atoi_long(const char *str, int *err_status)
{
	unsigned long long	num;
	int					i;
	int					sign;

	i = 0;
	sign = 1;
	num = 0;
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
		if ((sign == 1 && num > LONG_MAX) ||
			(sign == -1 && num > (unsigned long long)LONG_MAX + 1))
		{
			if (err_status)
				*err_status = 1;
			return (0);
		}
		i++;
	}
	return (sign * (long)num);
}
