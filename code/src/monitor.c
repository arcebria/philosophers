/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:44:15 by arcebria          #+#    #+#             */
/*   Updated: 2025/02/18 21:39:33 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	check_full(t_data *data)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while(i < data->n_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].meals_count >= data->meals)
			full++;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	if (full == data->n_philos)
	{
		pthread_mutex_lock(&data->end_mutex);
		printf("Todos llenos\n");
		data->end = true;
		pthread_mutex_unlock(&data->end_mutex);
	}
}

void	check_death(t_data *data)
{
	int	i;
	time_t	current_time;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		current_time = get_time() - data->philos[i].last_time_meal;
		pthread_mutex_unlock(&data->meal_mutex);
		pthread_mutex_lock(&data->end_mutex);
		if (current_time >= data->t_die)
		{
			data->end = true;
			pthread_mutex_unlock(&data->end_mutex);
			printf("<%ld> Philo %d is dead\n", get_time() - data->start_time, data->philos[i].id);
		}
		else
			pthread_mutex_unlock(&data->end_mutex);
		if (data->end == true)
			break ;
		i++;
	}
}

void	*monitor_health(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->end_mutex);
		if (data->end == true)
		{
			pthread_mutex_unlock(&data->end_mutex);
			return (NULL) ;
			//posible fallo en codic original
		}
		pthread_mutex_unlock(&data->end_mutex);
		check_death(data);
		if (data->meals > 0)
			check_full(data);
		ft_usleep(5);
	}
	return (NULL);
}
