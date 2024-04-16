/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:23 by hzibari           #+#    #+#             */
/*   Updated: 2024/04/16 21:50:06 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

# define MAX_PHILO 300

typedef struct t_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}					t_fork;

typedef struct s_philo
{
	int				id;
	bool			full;
	long			meal_count;
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*sec_fork;
	pthread_t		thread_id;
	pthread_mutex_t	eating_mtx;
	t_data			*data;
}				t_philo;

typedef struct t_data
{
	long			nbr_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_meals_limit;
	long			start_of_sim;
	bool			end_sim;
	bool			all_ready;
	pthread_mutex_t	ready_to_start;
	t_philo			*philos;
	t_fork			*forks;
}					t_data;

int		ft_atoi(const char *str);
int		ft_init(t_data *data, char **av);
int		start_sim(t_data *data);
void	destroy_all(t_data	*data);
void	*routine(void	*philo_struct);
long	get_time(void);

#endif