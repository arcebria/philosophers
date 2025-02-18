/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:09:08 by arcebria          #+#    #+#             */
/*   Updated: 2025/02/18 21:40:21 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	distribute_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i]->left_fork = (data->philos[i]->id - 1) % data->n_philos;
		data->philos[i]->right_fork = (data->philos[i]->id) % data->n_philos;
		i++;
	}
}

void	create_forks(t_data	*data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->n_philos * sizeof(pthread_mutex_t));
	if (!data->forks)
		error_exit(MEMORY_ERROR);
	while (i < data->n_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	create_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philos *) * data->n_philos);
	if (!data->philos)
		error_exit(MEMORY_ERROR);
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i] = malloc(sizeof(t_philos));
		if (!data->philos[i])
			error_exit(MEMORY_ERROR);
		data->philos[i]->last_time_meal = 0;
		data->philos[i]->id = i + 1;
		data->philos[i]->data = data;
		i++;
	}
}

int	init_struct(int ac, char **av)
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->n_philos = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->meals_flag = 0;
	data->full_count = 0;
	data->end_flag = false;
	data->full_flag = false;
	if (ac == 6)
	{
		data->meals = ft_atoi(av[5]);
		data->meals_flag = 1;
	}
	check_input(data, data->meals_flag);
	create_philos(data);
	create_forks(data);
	distribute_forks(data);
	run_philos(data);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac < 5)
		error_exit(0);
	if (init_struct(ac, av))
		error_exit(MEMORY_ERROR);
	return (0);
}
