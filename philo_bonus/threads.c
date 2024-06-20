/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:26:38 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/14 18:48:08 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_monitor(void *philo)
{
	t_single_philo	*p;
	t_philos		*info;
	int				philo_count;

	p = philo;
	info = p->info;
	philo_count = info->num_of_philos;
	while (1)
	{
		if (!check_meal_time(p))
		{
			sem_post(info->routine_lock);
			set_dead(p);
			sem_wait(p->writing);
			printf("%ld %d has died\n", get_time_ms() - info->start_time, p->phil_id);
			sem_post(p->writing);
			break ;
		}
	}
	(void)philo_count;
	return (NULL);
}

void	*main_monitor(void *philo)
{
	t_single_philo	*p;
	t_philos		*info;
	int				eaten;

	p = philo;
	info = p->info;
	eaten = 0;
	while (1)
	{
		if (eaten == info->num_of_philos)
		{
			sem_post(info->routine_lock);
			return (NULL);
		}
		sem_wait(info->ended);
		eaten++;
	}
	return (NULL);
}

void	*death(void *philos)
{
	t_single_philo	*p;
	t_philos		*info;
	int				i;

	p = philos;
	info = p->info;
	i = 0;
	sem_wait(info->routine_lock);
	// sem_post(p->writing);
	while (i < info->num_of_philos)
	{
		if (info->num_of_meals > 0)
			sem_post(info->ended);
		i++;
		// kill(info->pids[i++], SIGTERM);
	}
	// sem_post(info->break_routine);
	return (NULL);
}
