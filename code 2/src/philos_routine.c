/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:04:36 by arcebria          #+#    #+#             */
/*   Updated: 2025/02/17 21:01:56 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

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



int	check_end(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->end_mutex);
	if (philo->data->end_flag || philo->data->full_flag)
	{
		pthread_mutex_unlock(&philo->data->end_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->end_mutex);
	return (0);
}

int	eat_meal(t_philos *philo)
{
	if (check_end(philo))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return (1);
	}
	print_activity(philo, EAT);
	usleep(philo->data->t_eat * 1000);
	philo->last_time_meal = get_time();
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	return (0);
}

int	take_forks(t_philos *philo)
{
	if (check_end(philo))
		return (1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		if (check_end(philo))
			return (1);
		print_activity(philo, LEFT_FORK);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		if (check_end(philo))
			return (1);
		print_activity(philo, RIGHT_FORK);

	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		if (check_end(philo))
			return (1);
		print_activity(philo, RIGHT_FORK);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		if (check_end(philo))
			return (1);
		print_activity(philo, LEFT_FORK);
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	philo->meals_count = 0;
	philo->full = false;
	while (!check_end(philo))
	{
		print_activity(philo, THINK);
		if (take_forks(philo))
			break ;
		if (eat_meal(philo))
			break ;
		philo->meals_count++;
		//if (philo->meals_count == philo->data->meals)
		//	break ;
		if (check_end(philo))
			break ;
		print_activity(philo, SLEEP);
		usleep(philo->data->t_sleep * 1000);
	}
	return (NULL);
}

void	run_philos(t_data *data)
{
	int			i;
	pthread_t	philos[data->n_philos];
	pthread_t	monitor;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_create(&philos[i], NULL, philo_routine, data->philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_health, data);
	i = 0;
	pthread_join(monitor, NULL);
	while (i < data->n_philos)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
}
