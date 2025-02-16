/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:04:36 by arcebria          #+#    #+#             */
/*   Updated: 2025/02/16 21:11:19 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/*void	take_fork(t_philos *philo)
{
	int i = 0;
	while (i < 5)
	{
		printf("<%ld> Philo %d is thinking\n", get_time() - philo->data->start_time, philo->id);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
			printf("<%ld> Philo %d take left fork\n", get_time() - philo->data->start_time, philo->id);
			pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
			printf("<%ld> Philo %d take right fork\n", get_time() - philo->data->start_time, philo->id);
		}
		else
		{
			pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
			printf("<%ld> Philo %d take right fork\n", get_time() - philo->data->start_time, philo->id);
			pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
			printf("<%ld> Philo %d take left fork\n",get_time() - philo->data->start_time, philo->id);
		}
		printf("<%ld> Philo %d is eating\n", get_time() - philo->data->start_time, philo->id);
		usleep(100000);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		printf("<%ld> Philo %d has finished eating\n", get_time() - philo->data->start_time, philo->id);
		usleep(100000);
		i++;
	}
}*/

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

void	*monitor_health(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (data->im_dead == true)
			break ;
		usleep(1000);
	}
	return (NULL);
}

int	check_death(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (get_time() - philo->last_time_meal > philo->data->t_die)
	{
		philo->data->im_dead = true;
		print_activity(philo, DEATH);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death);
	philo->last_time_meal = get_time();
	return (0);
}

int	eat_meal(t_philos *philo)
{
	if (check_death(philo))
		return (1);
	print_activity(philo, EAT);
	usleep(philo->data->t_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	return (0);
}

int	take_forks(t_philos *philo)
{
	if (check_death(philo))
		return (1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_activity(philo, LEFT_FORK);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_activity(philo, RIGHT_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_activity(philo, RIGHT_FORK);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_activity(philo, LEFT_FORK);
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	philo->meals_count = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->im_dead == true)
		{
			pthread_mutex_unlock(&philo->data->death);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death);
		printf(RO"<%ld> Philo %d is thinking\n"R, get_time(), philo->id);
		if (take_forks(philo))
			break ;
		if (eat_meal(philo))
			break ;
		pthread_mutex_lock(&philo->data->count);
		philo->meals_count++;
		pthread_mutex_unlock(&philo->data->count);
		if (philo->meals_count == philo->data->meals)
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
	while (i < data->n_philos)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}
