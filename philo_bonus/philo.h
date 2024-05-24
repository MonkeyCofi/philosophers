/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:35:47 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/21 19:44:20 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_single_philo
{
	pthread_t		tid;
	int				phil_id;
	int				meals_eaten;
	int				*is_dead;
	int				*left_free;
	int				*right_free;
	size_t			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*eating_mutex;
	void			*info;
}	t_single_philo;

typedef struct s_philos
{
	int				num_of_philos;
	int				dead;
	int				num_of_meals;
	int				*forks_status;
	size_t			start_time;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	size_t			time_to_die;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	write_lock;
	t_single_philo	*philosophers;
}	t_philos;

#endif