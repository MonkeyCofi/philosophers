/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:08:41 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/12 11:11:53 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	not_dead(t_philos *p)
{
	pthread_mutex_lock(&p->dead_mutex);
	if (p->dead)
	{
		pthread_mutex_unlock(&p->dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&p->dead_mutex);
	return (1);
}

void	set_dead(t_single_philo *philo)
{
	pthread_mutex_lock(philo->dead_mutex);
	*philo->is_dead = 1;
	pthread_mutex_unlock(philo->dead_mutex);
}

void	check_meal_time(t_single_philo *p)
{
	pthread_mutex_lock(p->eating_mutex);
	if (p->last_meal < get_time_ms() - ((t_philos *)p->info)->time_to_die)
	{
		set_dead(p);
		pthread_mutex_lock(p->write_lock);
		printf("%ld %d died\n",
			get_time_ms() - ((t_philos *)p->info)->start_time, p->phil_id);
		pthread_mutex_unlock(p->write_lock);
	}
	pthread_mutex_unlock(p->eating_mutex);
}

int	fully_devoured(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
	pthread_mutex_lock(p->eating_mutex);
	if (p->meals_eaten == info->num_of_meals)
	{
		pthread_mutex_unlock(p->eating_mutex);
		return (1);
	}
	pthread_mutex_unlock(p->eating_mutex);
	return (0);
}
