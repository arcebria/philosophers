/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:44:15 by arcebria          #+#    #+#             */
/*   Updated: 2025/02/17 21:06:30 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->philos[i]->meals_count == data->meals)
		{
			if (data->philos[i]->full == false)
			{
				//colocar mutex
				printf("<%ld> Philo %d lleno. Ha comido %d\n", get_time(), data->philos[i]->id, data->meals);
				data->full_count++;
			}
			data->philos[i]->full = true;
			if (data->full_count == data->n_philos)
			{
				data->full_flag = true;
				pthread_mutex_unlock(&data->death_mutex);
				return ;
			}
		}
		if (get_time() - data->philos[i]->last_time_meal >= data->t_die)
		{
			print_activity(data->philos[i], DEATH);
			data->end_flag = true;
			pthread_mutex_unlock(&data->death_mutex);
			return ;
		}
		pthread_mutex_unlock(&data->death_mutex);
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
		if (data->end_flag == true || data->full_flag == true)
		{
			pthread_mutex_unlock(&data->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->end_mutex);
		check_death(data);
		usleep(100);
	}
	return (NULL);
}
