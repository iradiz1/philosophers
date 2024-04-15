/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:06:35 by hzibari           #+#    #+#             */
/*   Updated: 2024/04/15 11:51:59 by hzibari          ###   ########.fr       */
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
