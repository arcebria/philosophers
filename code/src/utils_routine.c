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

void	print_activity(t_philos *philo, int i)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->end_mutex);
	if (i == THINK)
		printf(RO"<%ld> Philo %d is thinking\n"R, get_time() - philo->data->start_time, philo->id);
	else if (i == LEFT_FORK)
		printf(AM"<%ld> Philo %d take left fork\n"R, get_time() - philo->data->start_time, philo->id);
	else if (i == RIGHT_FORK)
		printf(AM"<%ld> Philo %d take right fork\n"R, get_time() - philo->data->start_time, philo->id);
	else if (i == EAT)
		printf(AZ"<%ld> Philo %d is eating\n"R, get_time() - philo->data->start_time, philo->id);
	else if (i == SLEEP)
		printf(VE"<%ld> Philo %d is sleeping\n"R, get_time() - philo->data->start_time, philo->id);
	else if (i == DEATH)
		printf("<%ld> Philo %d is dead\n", get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->end_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(time_t time)
{
	time_t	elapsed;
	time_t	start_time;

	start_time = get_time();
	while (1)
	{
		elapsed = get_time() - start_time;
		if (elapsed >= time)
			break ;
		usleep(500);
	}
	return (1);
}
