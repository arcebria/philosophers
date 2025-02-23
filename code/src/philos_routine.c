/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:04:36 by arcebria          #+#    #+#             */
/*   Updated: 2025/02/18 21:40:49 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	check_end(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->end_mutex);
	if (philo->data->end_flag)
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
		pthread_mutex_unlock(&philo->data->forks_mutex[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks_mutex[philo->left_fork]);
		return (1);
	}
	print_activity(philo, EAT);
	//ft_usleep(philo->data->t_eat);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_time_meal = get_time();
	philo->meals_count++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_unlock(&philo->data->forks_mutex[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks_mutex[philo->left_fork]);
	return (0);
}


int	take_forks(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks_mutex[philo->left_fork]);
		if (check_end(philo))
			return (1);
		print_activity(philo, LEFT_FORK);
		pthread_mutex_lock(&philo->data->forks_mutex[philo->right_fork]);
		if (check_end(philo))
			return (1);
		print_activity(philo, RIGHT_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks_mutex[philo->right_fork]);
		if (check_end(philo))
			return (1);
		print_activity(philo, RIGHT_FORK);
		pthread_mutex_lock(&philo->data->forks_mutex[philo->left_fork]);
		if (check_end(philo))
			return (1);
		print_activity(philo, LEFT_FORK);
	}
	return (0);
}

int	get_sleep(t_philos *philo)
{
	if (check_end(philo))
		return (1);
	pthread_mutex_lock(&philo->data->meal_mutex);
	print_activity(philo, SLEEP);
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(philo->data->t_sleep);
	return (0);
}

int	think(t_philos *philo)
{
	if (check_end(philo))
		return (1);
	pthread_mutex_lock(&philo->data->meal_mutex);
	print_activity(philo, THINK);
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(5);
	return (0);
}

void	ph_delay(time_t t_start)
{
	while (get_time() < t_start)
		continue ;
}

void	*philo_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->data->n_philos == 1)
	{
		print_activity(philo, RIGHT_FORK);
		ft_usleep(philo->data->t_die);
		return (NULL);
	}
	ph_delay(philo->data->start_time);
	while (!check_end(philo))
	{
		if (take_forks(philo))
			break ;
		if (eat_meal(philo))
			break ;
		if (philo->meals_count == philo->data->meals)
			break ;
		if (get_sleep(philo))
			break ;
		if (think(philo))
			break ;
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
