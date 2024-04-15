/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:45:16 by halgordziba       #+#    #+#             */
/*   Updated: 2024/04/15 11:53:30 by hzibari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philos(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].full = false;
		data->philos[i].meal_count = 0;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % 5];
		data->philos->data = data;
		i++;
	}
}

static int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL))
			return (write(2, "pthread mutex init failed\n", 26), 1);
		data->forks[i].fork_id = i;
		i++;
	}
	return (0);
}

static int	init_data(t_data *data, char **av)
{
	struct timeval	time;

	data->nbr_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]) * 1000;
	data->time_to_eat = ft_atoi(av[3]) * 1000;
	data->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (av[5])
		data->nbr_meals_limit = ft_atoi(av[5]);
	else
		data->nbr_meals_limit = -1;
	if (gettimeofday(&time, NULL))
		return (write(2, "gettimeifday failed\n", 20), 1);
	data->end_sim = false;
	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (!data->philos)
		return (write(2, "philos malloc failed\n", 21), 1);
	data->forks = malloc(sizeof(t_fork) * data->nbr_of_philos);
	if (!data->forks)
		return (write(2, "forks malloc failed\n", 20), 1);
	return (0);
}

int	ft_init(t_data *data, char **av)
{
	if (init_data(data, av))
		return (1);
	if (init_forks(data))
		return (1);
	init_philos(data);
	return (0);
}
