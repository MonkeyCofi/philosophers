/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:38:15 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/18 17:13:24 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_meal_time(t_philos *p, int i)
{
	pthread_mutex_lock(&p->eating_mutex);
	if (get_time_ms() > p->philosophers[i].last_meal + p->time_to_die)
	{
		*p->philosophers[i].is_dead = 1;
		pthread_mutex_lock(p->philosophers[i].write_lock);
		printf("%ld %d has died\n", get_time_ms() - p->start_time, p->philosophers[i].phil_id);
		pthread_mutex_unlock(p->philosophers[i].write_lock);
	}
	pthread_mutex_unlock(&p->eating_mutex);
}
