/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:22:06 by halgordziba       #+#    #+#             */
/*   Updated: 2024/04/19 15:27:24 by hzibari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	thinking(t_philo *philo)
{
	print_msg(philo, "is thinking", philo->id);
}

static	void	sleeping(t_philo *philo)
{
	print_msg(philo, "is sleeping", philo->id);
	ft_usleep(philo->data->time_to_sleep);
}

static	long	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	print_msg(philo, "has taken first fork", philo->id);
	pthread_mutex_lock(&philo->sec_fork->fork);
	print_msg(philo, "has taken secound fork", philo->id);
	print_msg(philo, "is eating", philo->id);
	pthread_mutex_lock(&philo->eating_mtx);
	philo->last_meal_time = get_time();
	if (!philo->last_meal_time)
		return (1);
	philo->meal_count++;
	if (philo->meal_count == philo->data->nbr_meals_limit)
		philo->full = true;
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->eating_mtx);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->sec_fork->fork);
	return (0);
}

void	*routine(void	*philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	// pthread_mutex_lock(&philo->data->ready_to_start);
	// while (!philo->data->all_ready)
	// 	;
	// pthread_mutex_unlock(&philo->data->ready_to_start);
	while (1)
	{
		if (philo->full)
			break ;
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
