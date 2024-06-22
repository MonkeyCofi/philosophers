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

	p = philo;
	info = p->info;
	while (1)
	{
		if (all_meals_eaten(p))
			break ;
		if (!check_meal_time(p))
		{
			sem_wait(p->writing);
			printf("%ld %d has died\n", get_time_ms() - info->start_time, p->phil_id);
			sem_wait(info->ended);
			sem_post(info->break_routine);
			sem_post(info->ended);
			break ;
		}
	}
	return (NULL);
}

void	*detect_termination(void *philo_array)
{
	t_single_philo	*p;
	t_philos		*info;

	p = philo_array;
	info = p->info;
	if (!not_dead(info) || eaten_fully(info))
		exit(0);
	sem_wait(info->ended);
	sem_wait(info->break_routine);
	sem_post(info->ended);
	free(info->pids);
	free(p);
	sem_post(info->break_routine);
	close_sems(info, p, 0);
	exit(0);
}

void	*meal_thread(void *philos)
{
	t_single_philo	*p;
	t_philos		*info;

	p = philos;
	info = p->info;
	while (1)
	{
		if (!not_dead(info))
			break ;
		if (eaten_fully(info))
		{
			drop_right_fork(p);
			drop_left_fork(p);
			exit(0);
		}
	}
	exit(0);
}
