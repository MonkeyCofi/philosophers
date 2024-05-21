/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:10:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/21 17:46:58 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *ptr)
{
	t_single_philo	*p;
	t_philos		*info;

	p = ptr;
	info = p->info;
	if (p->phil_id % 2 && p->meals_eaten == 0)
		ft_usleep(info->time_to_eat / 2);
	while (not_dead(info))
	{
		philo_hungy(p);
		philo_eepy(p);
		philo_thinky(p);
	}
	return (NULL);
}

void	philo_hungy(t_single_philo *p)
{
	if (pick_forks(p))
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

void	philo_thinky(t_single_philo *p)
{
	print_message(p->info, p, "is thinking");
}

void	philo_devour(t_single_philo *p)
{
	t_philos	*ph;

	ph = p->info;
	print_message(ph, p, "is eating");
	pthread_mutex_lock(p->eating_mutex);
	p->last_meal = get_time_ms();
	p->meals_eaten++;
	pthread_mutex_unlock(p->eating_mutex);
	ft_usleep(ph->time_to_eat);
}
