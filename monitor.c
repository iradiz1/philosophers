/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:33:40 by hzibari           #+#    #+#             */
/*   Updated: 2024/05/06 14:15:14 by hzibari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	dead_cal(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->time_mtx);
	time = get_time();
	pthread_mutex_lock(&philo->data->dead_mtx);
	if (time - philo->last_meal_time >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->dead_mtx);
		pthread_mutex_unlock(&philo->data->time_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_mtx);
	pthread_mutex_unlock(&philo->data->time_mtx);
	return (0);
}

static int	check_if_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		if (dead_cal(&data->philos[i]))
		{
			print_msg(&data->philos[i], "died", data->philos[i].id);
			pthread_mutex_lock(&data->philos[i].data->dead_mtx);
			data->dead = true;
			pthread_mutex_unlock(&data->philos[i].data->dead_mtx);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_if_all_ate(t_data *data)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	pthread_mutex_lock(&data->philos->data->time_mtx);
	if (data->nbr_meals_limit == -1)
		return (pthread_mutex_unlock(&data->philos->data->time_mtx), 0);
	pthread_mutex_unlock(&data->philos->data->time_mtx);
	while (i < data->nbr_of_philos)
	{
		pthread_mutex_lock(&data->philos->data->time_mtx);
		if (data->philos[i].meal_count >= data->nbr_meals_limit)
			finished_eating++;
		pthread_mutex_unlock(&data->philos->data->time_mtx);
		i++;
	}
	if (finished_eating == data->nbr_of_philos)
	{
		pthread_mutex_lock(&data->philos->data->dead_mtx);
		data->dead = true;
		pthread_mutex_unlock(&data->philos->data->dead_mtx);
		return (1);
	}
	return (0);
}

void	*monitor(void	*data_struct)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_struct;
	while (1)
	{
		i = 0;
		if ((check_if_dead(data) == 1) || (check_if_all_ate(data) == 1))
			break ;
	}
	return (data_struct);
}
