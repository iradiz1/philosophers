/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:49:23 by hzibari           #+#    #+#             */
/*   Updated: 2024/04/29 13:24:34 by hzibari          ###   ########.fr       */
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

# define MAX_PHILO 200

typedef struct t_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}					t_fork;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	bool			full;
	long			meal_count;
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*sec_fork;
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
	bool			dead;
	pthread_mutex_t	time_mtx;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_mtx;
	t_philo			*philos;
	t_fork			*forks;
}					t_data;

int		ft_atoi(const char *str);
int		ft_init(t_data *data, char **av);
int		start_sim(t_data *data);
void	destroy_all(t_data	*data);
void	*routine(void	*philo_struct);
long	get_time(void);
void	ft_usleep(long millisecounds);
void	print_msg(t_philo *philo, char *msg, int id);
void	*monitor(void	*data_struct);
int		is_not_dead(t_philo *philo);
void	lone_philo(t_philo	*philo);

#endif
