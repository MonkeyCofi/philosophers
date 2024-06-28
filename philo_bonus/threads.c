/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:26:38 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/28 20:14:05 by pipolint         ###   ########.fr       */
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
			info->end = 1;
			sem_post(info->break_routine);
			sem_post(info->ended);
			break ;
		}
	}
	//printf("philo %d breaking from monitoring thread\n", p->phil_id);
	return (NULL);
}

int	ended(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
	sem_wait(info->ended);
	if (info->end)
	{
		sem_post(info->ended);
		return (1);
	}
	sem_post(info->ended);
	return (0);
}

void	*detect_termination(void *philo_array)
{
	t_single_philo	*p;
	t_philos		*info;

	p = philo_array;
	info = p->info;
	while (!ended(p))
	{
		if (!not_dead(info) || eaten_fully(info))
			break ;
		usleep(250);
	}
	//printf("returning from termination thread\n");
	sem_wait(info->break_routine);
	free(info->pids);
	//free(p);
	sem_post(info->break_routine);
	//close_sems(info, p, 0);
	return (NULL);
	//exit(0);
}

void	*meal_thread(void *philos)
{
	t_single_philo	*p;
	t_philos		*info;

	p = philos;
	info = p->info;
	while (!ended(p))
	{
		if (!not_dead(info))
		{
			drop_right_fork(p);
			drop_left_fork(p);
			break ;
		}
		if (eaten_fully(info))
		{
			drop_right_fork(p);
			drop_left_fork(p);
			break ;
		}
	}
	//printf("returning from meal thread\n");
	return (NULL);
	//exit(0);
}
