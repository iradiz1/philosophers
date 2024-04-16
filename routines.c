/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:22:06 by halgordziba       #+#    #+#             */
/*   Updated: 2024/04/17 00:07:09 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	thinking(t_philo *philo)
{
	printf("%zu %d %s\n", get_time(), philo->id, "is thinking");
}

static	void	sleeping(t_philo *philo)
{
	printf("%zu %d %s\n", get_time(), philo->id, "is sleeping");
	// usleep(philo->data->time_to_sleep * 1000);
}

static  long	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	printf("%zu %d %s\n", get_time(), philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->sec_fork->fork);
	printf("%zu %d %s\n", get_time(), philo->id, "has taken a fork");
	printf("%zu %d %s\n", get_time(), philo->id, "is eating");
	pthread_mutex_lock(&philo->eating_mtx);
	philo->meal_count++;
	if (philo->meal_count == philo->data->nbr_meals_limit)
		philo->full = true;
	pthread_mutex_unlock(&philo->eating_mtx);
	// usleep(philo->data->time_to_eat * 1000);
	philo->last_meal_time = get_time();
	if (!philo->last_meal_time)
		return (1);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->sec_fork->fork);
	return (0);
}

void	*routine(void	*philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	// while (!philo->data->all_ready)
	// 	;
	while (!philo->data->end_sim)
	{
		if (philo->full)
			break;
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return(routine);
}
