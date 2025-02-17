/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:04:36 by arcebria          #+#    #+#             */
/*   Updated: 2025/02/17 12:55:56 by arcebria         ###   ########.fr       */
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

void	*monitor_health(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->print);
		if (data->im_dead == true)
		{
			pthread_mutex_unlock(&data->print);
			break ;
		}
		pthread_mutex_unlock(&data->print);
		usleep(1000);
	}
	return (NULL);
}

void	check_death(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (get_time() - philo->last_time_meal > philo->data->t_die)
	{
		philo->data->im_dead = true;
		printf("<%ld> Philo %d is dead\n", get_time(), philo->id);
	}
	pthread_mutex_unlock(&philo->data->print);
	philo->last_time_meal = get_time();
}

void	eat_meal(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->print);
	check_death(philo);
	printf(AZ"<%ld> Philo %d is eating\n"R, get_time(), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	usleep(philo->data->t_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void	take_forks(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		printf(AM"<%ld> Philo %d take left fork\n"R, get_time(), philo->id);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		printf(AM"<%ld> Philo %d take right fork\n"R, get_time(), philo->id);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		printf(AM"<%ld> Philo %d take right fork\n"R, get_time(), philo->id);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		printf(AM"<%ld> Philo %d take left fork\n"R,get_time(), philo->id);
	}
}

void	*philo_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	philo->meals_count = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->data->print);
		if (philo->data->im_dead == true)
		{
			pthread_mutex_unlock(&philo->data->print);
			break ;
		}
		pthread_mutex_unlock(&philo->data->print);
		printf(RO"<%ld> Philo %d is thinking\n"R, get_time(), philo->id);
		take_forks(philo);
		eat_meal(philo);
		philo->meals_count++;
		if (philo->meals_count == philo->data->meals)
			break ;
		printf(AZ"<%ld> Philo %d is sleeping\n"R, get_time(), philo->id);
		usleep(philo->data->t_sleep * 1000);
	}
	return (NULL);
}

void	run_philos(t_data *data)
{
	int			i;

	data->philo_threads = malloc(sizeof(pthread_t) * data->n_philos);
	i = 0;
	while (i < data->n_philos)
	{
		pthread_create(&data->philo_threads[i], NULL, philo_routine, data->philos[i]);
		i++;
	}
	pthread_create(&data->monitor, NULL, monitor_health, data);
	pthread_join(data->monitor, NULL);
}
