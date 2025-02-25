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

void	output(char *s1, char *s2, char *s3)
{
	printf("%s", s1);
	printf("%s", s2);
	printf("%s\n", s3);
}

void	error_exit(int type, t_data *data)
{
	if (type == 0)
		output("Usage: ", USAGE, OPTIONAL);
	else if (type == 1)
		output("Invalid input", "", "");
	else if (type == 2)
		output("Error allocating memory", "", "");
	if (data)
		free(data);
	exit (1);
}
