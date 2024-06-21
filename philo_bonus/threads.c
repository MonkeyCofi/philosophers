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
			set_dead(p);
			sem_wait(p->writing);
			printf("%ld %d has died\n", get_time_ms() - info->start_time, p->phil_id);
			sem_post(info->break_routine);
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
	// if (!not_dead(info) || eaten_fully(info))
	// 	return (NULL);
	while (not_dead(info) && !eaten_fully(info))
	{
		sem_wait(info->break_routine);
		free(info->pids);
		free(p);
		sem_post(info->break_routine);
		// close_sems(info, p, 0);
		sem_close(info->break_routine);
		sem_close(info->dead_sem);
		exit(EXIT_SUCCESS);
	}
	return (NULL);
}

void	*main_thread(void *info)
{
	t_philos	*p;
	int			i;
	int			num_of_philos;

	p = info;
	i = -1;
	num_of_philos = p->num_of_philos;
	while (++i < num_of_philos)
		kill(p->pids[i], SIGQUIT);
	return (NULL);
}