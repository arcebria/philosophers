#include "../inc/philosophers.h"

int		ft_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			if (str[i] != '+' && str[i] != '-')
				return (0);
		}
		i++;
	}
	return (1);
}

void	check_syntax(t_data *data, char **av)
{
	int	i;
	
	i = 0;
	while (av[++i])
	{
		if (!ft_is_digit(av[i]))
			error_exit(INPUT_ERROR, data);
	}
}

int	ft_atoi(char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}