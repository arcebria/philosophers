/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:16:45 by arcebria          #+#    #+#             */
/*   Updated: 2025/02/18 21:39:42 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	lock_left_fork(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	if (check_end(philo))
		return (1);
	print_activity(philo, LEFT_FORK);
	return (0);
}

int	lock_right_fork(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	if (check_end(philo))
		return (1);
	print_activity(philo, RIGHT_FORK);
	return (0);
}

void	print_activity(t_philos *philo, int i)
{
	pthread_mutex_lock(&philo->data->print);
	if (i == THINK)
		printf(RO"<%ld> Philo %d is thinking\n"R, get_time(), philo->id);
	else if (i == LEFT_FORK)
		printf(AM"<%ld> Philo %d take left fork\n"R, get_time(), philo->id);
	else if (i == RIGHT_FORK)
		printf(AM"<%ld> Philo %d take right fork\n"R, get_time(), philo->id);
	else if (i == EAT)
		printf(AZ"<%ld> Philo %d is eating\n"R, get_time(), philo->id);
	else if (i == SLEEP)
		printf(AZ"<%ld> Philo %d is sleeping\n"R, get_time(), philo->id);
	else if (i == DEATH)
		printf("<%ld> Philo %d is dead\n", get_time(), philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

long	get_time(void)
{
	struct timeval	tv;
	static long		start_time = 0;
	static long		current_time;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (start_time == 0)
		start_time = current_time;
	return (current_time - start_time);
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


