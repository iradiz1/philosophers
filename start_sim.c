/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 10:39:29 by halgordziba       #+#    #+#             */
/*   Updated: 2024/04/16 23:48:53 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, &routine,
				&data->philos[i]))
			return (write(2, "pthread create failed\n", 22), 1);
		i++;
	}
	return (0);
}
static	int	join_threads(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL))
			return (write(2, "pthread join failed\n", 20), 1);
		i++;
	}
	return (0);
}

int	start_sim(t_data *data)
{
	if (data->nbr_meals_limit == 0)
		return (0);
	else
		if (create_threads(data))
			return (1);
	data->start_of_sim = get_time();
	pthread_mutex_lock(&data->ready_to_start);
	data->all_ready = true;
	pthread_mutex_unlock(&data->ready_to_start);
	if (join_threads(data))
		return (1);
	return (0);
}
