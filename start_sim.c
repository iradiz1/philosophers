/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 10:39:29 by halgordziba       #+#    #+#             */
/*   Updated: 2024/04/29 13:23:02 by hzibari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lone_philo(t_philo	*philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	print_msg(philo, "has taken a fork", philo->id);
	pthread_mutex_unlock(&philo->first_fork->fork);
	ft_usleep(philo->data->time_to_die);
}

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
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
			return (write(2, "pthread join failed\n", 20), 1);
		i++;
	}
	return (0);
}

int	start_sim(t_data *data)
{
	pthread_t	moni;

	if (data->nbr_meals_limit == 0)
		return (0);
	else
	{
		if (create_threads(data))
			return (1);
		if (pthread_create(&moni, NULL, &monitor, data))
			return (write(2, "pthread create failed\n", 22), 1);
	}
	if (join_threads(data))
		return (1);
	if (pthread_join(moni, NULL) != 0)
		return (write(2, "pthread join failed\n", 20), 1);
	return (0);
}
