/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:10:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/06 21:11:05 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	need_fork(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
	while (1)
	{
		if (p->left_free)
		{
			pthread_mutex_lock(p->left_fork);
			print_message(p->info, p, "has taken a fork");
			p->left_free = 0;
		}
		if (p->right_free)
		{
			pthread_mutex_lock(p->right_fork);
			print_message(p->info, p, "has taken a fork");
			p->right_free = 0;
		}
		if (!p->left_free || !p->right_free)
			break ;
	}
}

void	philo_devour(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
	print_message(p->info, p, "is eating");
	if (!info->dead)
		need_fork(p);
	pthread_mutex_lock(p->eating_mutex);
	p->meals_eaten++;
	p->last_meal = get_time_ms();
	p->left_free = 1;
	p->right_free = 1;
	ft_usleep(info->time_to_eat);
	pthread_mutex_unlock(p->eating_mutex);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void	philo_eepy(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
	ft_usleep(info->time_to_sleep);
	print_message(info, p, "is sleeping");
}

void	*monitor(void *philos)
{
	t_philos	*p;
	int			i;
	
	i = 0;
	p = philos;
	while (!p->dead)
	{
		if (i == p->num_of_philos)
			i = 0;
		if (get_time_ms() > p->philosophers[i].last_meal + p->time_to_die)
		{
			pthread_mutex_lock(p->philosophers[i].write_lock);
			printf("%ld %d has died\n", get_time_ms() - p->start_time, p->philosophers[i].phil_id);
			pthread_mutex_unlock(p->philosophers[i].write_lock);
			*p->philosophers[i].is_dead = 1;
			p->philosophers[i].has_died = 1;
		}
		i++;
	}
	return (NULL);
}
