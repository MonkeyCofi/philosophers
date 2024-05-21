/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:08:41 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/21 18:04:49 by pipolint         ###   ########.fr       */
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

void	set_dead(t_philos *p, t_single_philo *philo)
{
	pthread_mutex_lock(&p->dead_mutex);
	*philo->is_dead = 1;
	pthread_mutex_unlock(&p->dead_mutex);
}

void	check_meal_time(t_philos *p, int i)
{
	pthread_mutex_lock(&p->eating_mutex);
	if (p->philosophers[i].last_meal < get_time_ms() - p->time_to_die)
	{
		set_dead(p, &p->philosophers[i]);
		pthread_mutex_lock(p->philosophers[i].write_lock);
		printf("%ld %d has died\n",
			get_time_ms() - p->start_time, p->philosophers[i].phil_id);
		pthread_mutex_unlock(p->philosophers[i].write_lock);
	}
	pthread_mutex_unlock(&p->eating_mutex);
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
