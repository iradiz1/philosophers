/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:06:35 by hzibari           #+#    #+#             */
/*   Updated: 2024/04/19 15:23:24 by hzibari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int long		i;
	int long		m;
	int long long	p;

	i = 0;
	m = 1;
	p = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			m *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		p = p * 10 + (str[i] - 48);
		i++;
	}
	if (p * m > 2147483647 || p * m < -2147483648)
		return (write(2, "atoi error\n", 11), 1);
	return (p * m);
}

void	destroy_all(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
		i++;
	}
	free(data->forks);
	free(data->philos);
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (write(2, "gettimeifday failed\n", 20), 0);
	return (time.tv_sec * 1000 + time.tv_sec / 1000);
}

void	ft_usleep(long millisecounds)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < millisecounds)
		usleep(500);
	return ;
}

void	print_msg(t_philo *philo, char *msg, int id)
{
	long	time;

	pthread_mutex_lock(&philo->data->print_lock);
	time = get_time() - philo->start_of_sim;
	printf("%zu %d %s\n", time, id, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
}
