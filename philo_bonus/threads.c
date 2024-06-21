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
			sem_post(info->ended);
			// sem_post(p->writing);
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
	if (!not_dead(info) || eaten_fully(info))
		return (NULL);
	sem_wait(info->break_routine);
	free(info->pids);
	free(p);
	sem_post(info->break_routine);
	// close_sems(info, p);
	exit(EXIT_SUCCESS);
	// while (1)
	// {
	// 	if (!not_dead(info))
	// 	  	break ;
	// 	if (eaten_fully(info))
	// 		break ;
	// 	sem_wait(info->break_routine);
	// 	free(info->pids);
	// 	free(philo_array);
	// 	sem_post(info->break_routine);
	// 	exit(EXIT_SUCCESS);
	// }
	return (NULL);
}

void	*main_thread(void *info)
{
	t_philos	*p;

	p = info;
	(void)p;
	return (NULL);
}