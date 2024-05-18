/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:10:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/18 20:52:47 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_devour(t_single_philo *p)
{
	t_philos	*ph;

	ph = p->info;
	if (not_dead(ph))
	{
		print_message(ph, p, "is eating");
		ft_usleep(ph->time_to_eat);
		pthread_mutex_lock(p->eating_mutex);
		p->meals_eaten++;
		p->last_meal = get_time_ms();
		pthread_mutex_unlock(p->eating_mutex);
	}
}

void	philo_hungy(t_single_philo *p)
{
	t_philos	*info;
	
	info = p->info;
	if (not_dead(info) && pick_forks(p))
	{
		philo_devour(p);
		drop_forks(p);
	}
}

void	philo_eepy(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
	print_message(info, p, "is sleeping");
	ft_usleep(info->time_to_sleep);
}

void	*philo_routine(void *ptr)
{
	t_single_philo	*p;
	t_philos		*info;

	p = ptr;
	info = p->info;
	if (p->phil_id % 2)
		ft_usleep(info->time_to_die / 2);
	while (not_dead(info))
	{
		philo_hungy(p);
		pthread_mutex_lock(p->eating_mutex);
		if (p->meals_eaten == info->num_of_meals)
		{
			pthread_mutex_unlock(p->eating_mutex);
			break ;
		}
		pthread_mutex_unlock(p->eating_mutex);
		philo_eepy(p);
		print_message(info, p, "is thinking");
	}
	return (NULL);
}
