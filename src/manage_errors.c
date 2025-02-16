/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:19:25 by arcebria          #+#    #+#             */
/*   Updated: 2025/02/12 18:33:45 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	output(char *s1, char *s2, char *s3)
{
	int	i;

	i = 0;
	while (s1[i])
		write(2, &s1[i++], ft_strlen(s1));
	i = 0;
	while (s2[i])
		write(2, &s2[i++], ft_strlen(s2));
	i = 0;
	while (s3[i])
		write(2, &s3[i++], ft_strlen(s3));
	write(2, "\n", 1);
}

void	error_exit(int type)
{
	if (type == 0)
		output("Usage: ", USAGE, OPTIONAL);
	else if (type == 1)
		output("Invalid input", "", "");
	else if (type == 2)
		output("Error allocating memory", "", "");
	exit (1);
}

void	check_input(t_data *data, int flag)
{
	if (data->n_philos <= 0)
		error_exit(1);
	if (data->t_die <= 0)
		error_exit(1);
	if (data->t_eat <= 0)
		error_exit(1);
	if (data->t_sleep <= 0)
		error_exit(1);
	if (flag)
	{
		if (data->meals <= 0)
		error_exit(INPUT_ERROR);
	}
}
