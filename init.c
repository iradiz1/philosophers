/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:45:16 by halgordziba       #+#    #+#             */
/*   Updated: 2024/04/26 13:48:00 by hzibari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philos(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		data->philos[i].last_meal_time = get_time();
		data->philos[i].id = i + 1;
		data->philos[i].full = false;
		data->philos[i].meal_count = 0;
		data->philos[i].sec_fork = &data->forks[i];
		data->philos[i].first_fork = &data->forks[(i + 1)
			% data->nbr_of_philos];
		if (data->philos[i].id % 2 == 0)
		{
			data->philos[i].first_fork = &data->forks[i];
			data->philos[i].sec_fork = &data->forks[(i + 1)
				% data->nbr_of_philos];
		}

		data->philos[i].data = data;
		i++;
	}
	return (0);
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
	data->nbr_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->start_of_sim = get_time();
	data->dead = false;
	if (av[5])
		data->nbr_meals_limit = ft_atoi(av[5]);
	else
		data->nbr_meals_limit = -1;
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (write(2, "pthread mutex init failed\n", 26), 1);
	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (!data->philos)
		return (write(2, "philos malloc failed\n", 21), 1);
	data->forks = malloc(sizeof(t_fork) * data->nbr_of_philos);
	if (!data->forks)
		return (write(2, "forks malloc failed\n", 20), 1);
	if (pthread_mutex_init(&data->dead_mtx, NULL))
		return (write(2, "pthread mutex init failed\n", 26), 1);
	if (pthread_mutex_init(&data->time_mtx, NULL))
		return (write(2, "pthread mutex init failed\n", 26), 1);
	return (0);
}

int	ft_init(t_data *data, char **av)
{
	if (init_data(data, av))
		return (1);
	if (init_forks(data))
		return (1);
	if (init_philos(data))
		return (1);
	return (0);
}
