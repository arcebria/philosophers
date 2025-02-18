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

typedef struct s_data	t_data;

typedef struct s_philos
{
	int		id;
	int		right_fork;
	int		left_fork;
	int		meals_count;
	int		last_time_meal;
	bool	full;
	t_data	*data;
}	t_philos;

typedef struct s_data
{
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				meals;
	int				meals_flag;
	int				full_count;
	bool			full_flag;
	bool			end_flag;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	t_philos		**philos;
}	t_data;

void	output(char *s1, char *s2, char *s3);
void	error_exit(int type);
void	check_input(t_data *data, int flag);
void	init_pthreads(t_data *data);
long	get_time(void);
int		ft_atoi(char *str);
void	*philo_routine(void *arg);
void	*monitor_health(void *arg);
void	run_philos(t_data *data);
void	print_activity(t_philos *philo, int i);
int		lock_left_fork(t_philos *philo);
int		lock_right_fork(t_philos *philo);
int		check_end(t_philos *philo);

#endif
