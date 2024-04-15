/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 10:39:29 by halgordziba       #+#    #+#             */
/*   Updated: 2024/04/15 03:09:27 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine()
{
	if (data->philos.id % 2 == 0)
		pthread_mutex_lock(data->philos->l_fork.fork);
	
	return (0);
}

static int	create_threads(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, &routine, data))
		{
			destroy_all(data);
			return (write(2, "pthread create failed\n", 22), 1);
		}
		i++;
	}
	i = 0;
	while (i < data->nbr_of_philos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL))
		{
			destroy_all(data);
			return (write(2, "pthread join failed\n", 20), 1);
		}
		i++;
	}
	return (0);
}

int start_sim(t_data *data)
{
	if (data->nbr_meals_limit == 0)
		return (0);
	return (0);
	
}