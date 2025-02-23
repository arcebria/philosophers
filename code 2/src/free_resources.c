
#include "../inc/philosophers.h"

void    free_structs(t_data *data)
{
    int i;

    free(data->forks_mutex);
    i = 0;
    while (i < data->n_philos)
    {
        free(data->philos[i]);
        i++;
    }
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
        pthread_mutex_destroy(&data->forks_mutex[i]);
        i++;
    }
}

void    free_resources(t_data *data)
{
    free_mutex(data);
    free_structs(data);
}