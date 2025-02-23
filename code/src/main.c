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
	data->forks_mutex = malloc(data->n_philos * sizeof(pthread_mutex_t));
	if (!data->forks_mutex)
		error_exit(MEMORY_ERROR, data);
	while (i < data->n_philos)
	{
		pthread_mutex_init(&data->forks_mutex[i], NULL);
		i++;
	}
}

void	create_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philos *) * data->n_philos);
	if (!data->philos)
		error_exit(MEMORY_ERROR, data);
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i] = malloc(sizeof(t_philos));
		if (!data->philos[i])
			error_exit(MEMORY_ERROR, data);
		data->philos[i]->last_time_meal = get_time();
		data->philos[i]->meals_count = 0;
		data->philos[i]->id = i + 1;
		data->philos[i]->data = data;
		i++;
	}
}

void	parsing(t_data *data, int ac, char **av)
{
	check_syntax(data, av);
	data->n_philos = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->meals_flag = 0;
	if (ac == 6)
	{
		data->meals = ft_atoi(av[5]);
		data->meals_flag = 1;
	}
	else
		data->meals = 0;
	check_input(data, data->meals_flag);
}

int	init_struct(int ac, char **av)
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	parsing(data, ac, av);
	data->end_flag = false;
	data->start_time = get_time(); //+ (data->n_philos * 2 * 10);
	pthread_mutex_init(&data->end_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	create_philos(data);
	create_forks(data);
	distribute_forks(data);
	run_philos(data);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		error_exit (USAGE_ERROR, NULL);
	if (init_struct(ac, av))
		error_exit(MEMORY_ERROR, NULL);
	return (0);
}
