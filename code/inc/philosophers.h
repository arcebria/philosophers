/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:17:03 by arcebria          #+#    #+#             */
/*   Updated: 2025/02/18 21:33:55 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

# define USAGE "<number_of_philos> <time_to_die> <time_to_eat> <time_to_sleep>"
# define OPTIONAL " <number_times_each_philosopher_must_eat(optional)>"
# define USAGE_ERROR 0
# define INPUT_ERROR 1
# define MEMORY_ERROR 2

# define THINK 0
# define LEFT_FORK 1
# define RIGHT_FORK 2
# define EAT 3
# define SLEEP 4
# define DEATH 5

# define RO "\033[31m"
# define VE "\033[32m"
# define AM "\033[33m"
# define AZ "\033[34m"
# define R "\033[0m"

//typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_philos
{
	int					id;
	int					meals_count;
	time_t				last_time_meal;
	t_fork				*right_fork;
	t_fork				*left_fork;
	pthread_t			philo_thread;
	struct s_data		*data;
}	t_philos;

typedef struct s_data
{
	int					n_philos;
	int					meals;
	int					meals_flag;
	time_t				t_die;
	time_t				t_eat;
	time_t				t_sleep;
	time_t				start_time;
	bool				end;
	bool				full;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		end_mutex;
	pthread_mutex_t		print_mutex;
	t_fork				*forks;
	t_philos			*philos;
}	t_data;

void	output(char *s1, char *s2, char *s3);
void	error_exit(int type, t_data *data);
void	check_input(t_data *data, int flag);
time_t	get_time(void);
int		ft_atoi(char *str);
void	*philo_routine(void *arg);
void	*monitor_health(void *arg);
void	run_philos(t_data *data, pthread_t *monitor);
void	print_activity(t_philos *philo, int i);
int		check_end(t_philos *philo);
int		ft_usleep(time_t time);
void	check_syntax(t_data *data, char **av);

#endif
