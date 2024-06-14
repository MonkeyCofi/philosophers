/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:26:38 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/14 17:12:32 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//}

void	*philo_monitor(void *philo)
{
	t_single_philo	*p;
	t_philos		*info;

	p = philo;
	info = p->info;
	while (1)
	{
		if (all_meals_eaten(p))
		{
			sem_post(info->ended);
			break ;
		}
		if (!check_meal_time(p))
		{
			sem_post(info->routine_lock);
			p->end = 1;
			sem_wait(p->writing);
			printf("%ld %d has died\n", get_time_ms() - info->start_time, p->phil_id);
			close_sems(info, p);
			break ;
		}
	}
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
	while (i < info->num_of_philos)
	{
		if (info->num_of_meals > 0)
			sem_post(info->ended);
		kill(info->pids[i++], SIGQUIT);
	}
	return (NULL);
}
