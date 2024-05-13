/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:22:06 by halgordziba       #+#    #+#             */
/*   Updated: 2024/05/13 13:04:58 by hzibari          ###   ########.fr       */
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

static	void	thinking(t_philo *philo)
{
	print_msg(philo, "is thinking", philo->id);
	usleep(500);
}

static	void	sleeping(t_philo *philo)
{
	print_msg(philo, "is sleeping", philo->id);
	ft_usleep(philo->data->time_to_sleep);
}

static	long	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	print_msg(philo, "has taken a fork", philo->id);
	pthread_mutex_lock(&philo->sec_fork->fork);
	print_msg(philo, "has taken a fork", philo->id);
	print_msg(philo, "is eating", philo->id);
	pthread_mutex_lock(&philo->data->time_mtx);
	philo->last_meal_time = get_time();
	if (!philo->last_meal_time)
		return (1);
	philo->meal_count++;
	if (philo->meal_count == philo->data->nbr_meals_limit)
		philo->full = true;
	pthread_mutex_unlock(&philo->data->time_mtx);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->sec_fork->fork);
	return (0);
}

void	*routine(void	*philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	if (philo->data->nbr_of_philos == 1)
		lone_philo(philo);
	if (philo->id % 2 == 0)
		thinking(philo);
	while (!is_not_dead(philo))
	{
		if (philo->full)
			break ;
		if (!is_not_dead(philo) || !philo->full)
			eating(philo);
		if (!is_not_dead(philo) || !philo->full)
			sleeping(philo);
		if (!is_not_dead(philo) || !philo->full)
			thinking(philo);
	}
	return (NULL);
}
