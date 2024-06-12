/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:26:38 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/12 21:57:39 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	the monitor thread for every philosopher
	this thread will check whether the philosopher has died, or has eaten all the required amount of meals
	if either is true, it will post sem_monitor, which will be waited for in the main process
*/
void	*philo_monitor(void *philo)
{
	t_single_philo	*p;
	t_philos		*info;

	p = philo;
	info = p->info;
	while (1)
	{
		if (all_meals_eaten(p))
			break ;
		if (!check_meal_time(p))
		{
			sem_post(info->monitor_sem);
			break ;
		}
	}
	return (NULL);
}

void	*main_monitor(void *philo)
{
	t_single_philo	*p;
	t_philos		*info;

	p = philo;
	info = p->info;
	sem_wait(info->monitor_sem);
	int i = 0;
	while (i < info->num_of_philos)
	{
		kill(info->pids[i++], SIGKILL);
	}
	return (NULL);
}
