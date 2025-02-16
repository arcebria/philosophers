/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:17:03 by arcebria          #+#    #+#             */
/*   Updated: 2025/02/16 21:08:46 by arcebria         ###   ########.fr       */
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

# define AZ "\033[34m"
# define RO "\033[31m"
# define AM "\033[33m"
# define R "\033[0m"

typedef	struct	s_data t_data;

typedef	struct s_philos
{
	int		id;
	int		right_fork;
	int		left_fork;
	int		meals_count;
	int		last_time_meal;
	//bool	im_dead;
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
	//long			start_time;
	//long			current_time;
	bool			im_dead;
	//int				id;
	pthread_mutex_t	count;
	pthread_mutex_t	death;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	t_philos		**philos;
}	t_data;

void	output(char *s1, char *s2, char *s3);
void	error_exit(int type);
void	check_input(t_data *data, int flag);
void	init_pthreads(t_data *data);
long	get_time();
int		ft_atoi(char *str);
void	*philo_routine(void *arg);
void	run_philos(t_data *data);

#endif
