/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:29 by hzibari           #+#    #+#             */
/*   Updated: 2024/04/29 13:30:40 by hzibari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_content(char *av)
{
	int	c;

	c = 0;
	while (av[c] != '\0')
	{
		if (av[c] < '0' || av[c] > '9')
			return (1);
		c++;
	}
	return (0);
}

static int	ft_check_input(char **av)
{
	if (ft_atoi(av[1]) > MAX_PHILO || ft_atoi(av[1]) < 1
		|| ft_check_content(av[1]) == 1)
		return (write(2, "invalid amount of philosophers\n", 31), 1);
	if (ft_atoi(av[2]) < 1 || ft_check_content(av[2]) == 1)
		return (write(2, "invalid time to die\n", 20), 1);
	if (ft_atoi(av[3]) < 1 || ft_check_content(av[3]) == 1)
		return (write(2, "invalid time to eat\n", 20), 1);
	if (ft_atoi(av[4]) < 1 || ft_check_content(av[4]) == 1)
		return (write(2, "invalid time to sleep\n", 22), 1);
	if (av[5] && (ft_atoi(av[5]) < 0 || ft_check_content(av[5]) == 1))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (write(2, "invalid argument count\n", 23), 1);
	if (ft_check_input(av))
		return (1);
	if (ft_init(&data, av))
		return (destroy_all(&data), 1);
	if (start_sim(&data))
		return (destroy_all(&data), 1);
	destroy_all(&data);
	return (0);
}
