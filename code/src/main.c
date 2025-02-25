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

/*void	distribute_forks(t_data *data)
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
}*/

void    free_structs(t_data *data)
{
    free(data->forks);
    free(data->philos);
    free(data);
}

void    free_mutex(t_data *data)
{
    int i;

    i = 0;
    pthread_mutex_destroy(&data->end_mutex);
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->meal_mutex);
    while(i < data->n_philos)
    {
        pthread_mutex_destroy(&data->forks[i].fork_mutex);
        i++;
    }
}

void    free_resources(t_data *data)
{
    free_mutex(data);
    free_structs(data);
}

void	join_threads(t_data *data, pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(data->philos[i].philo_thread, NULL);
		i++;
		//mirar si en el original li estic enviant els hilos i no la estructura
	}
	pthread_join(monitor, NULL);
}

void	run_threads(t_data *data, pthread_t *monitor)
{
	int			i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_create(&data->philos[i].philo_thread, NULL, philo_routine, &data->philos[i]);
		i++;
	}
	pthread_create(monitor, NULL, monitor_health, data);
}

void	create_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philos) * data->n_philos);
	data->forks = malloc(sizeof(t_fork) * data->n_philos);
	if (!data->philos || !data->forks)
		error_exit(MEMORY_ERROR, data);
	i = 0;
	while (i < data->n_philos)
	{
		//tot aço necessite entendreu
		pthread_mutex_init(&data->forks[i].fork_mutex, NULL);
		data->philos[i].id = i + 1;
		data->philos[i].last_time_meal = get_time();
		data->philos[i].meals_count = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->n_philos];
		data->philos[i].data = data;
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

void	init_struct(t_data *data)
{
	data->end = false;
	data->start_time = get_time();
	pthread_mutex_init(&data->end_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}

int	main(int ac, char **av)
{
	t_data		*data;
	pthread_t	monitor;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (ac != 5 && ac != 6)
		error_exit (USAGE_ERROR, NULL);
	parsing(data, ac, av);
	init_struct(data);
	create_philos(data);
	run_threads(data, &monitor);
	join_threads(data, monitor);
	free_resources(data);
	return (0);
}
