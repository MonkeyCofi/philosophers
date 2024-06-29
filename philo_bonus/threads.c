/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:26:38 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/29 15:27:19 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief monitor the philosopher until they die or ate fully
/// @param philo the philosopher
/// @return returns NULL
void	*philo_monitor(void *philo)
{
	t_single_philo	*p;
	t_philos		*info;

	p = philo;
	info = p->info;
	while (1)
	{
		check_meal_time(p);
		if (eaten_fully(info) || !not_dead(info))
		{
			sem_wait(info->writing);
			printf("%ld %d has died\n", get_time_ms() - info->start_time, p->phil_id);
			sem_post(info->send_kill);
			sem_post(info->freeing);
			break ;
		}
		usleep(100);
	}
	printf("broken out of monitor loop\n");
	return (NULL);
}

void	*free_resources(void *philo_array)
{
	t_single_philo	*philos;
	t_philos		*info;

	philos = philo_array;
	info = philos->info;
	sem_wait(info->freeing);
	printf("freeing\n");
	return (NULL);
}

void	*kill_philosophers(void *philo_array)
{
	t_single_philo	*philos;
	t_philos		*info;
	int				philo_count;
	int				iterate;
	pid_t			*pids;

	philos = philo_array;
	info = philos->info;
	philo_count = info->num_of_philos;
	iterate = -1;
	pids = info->pids;
	sem_wait(info->send_kill);
	sem_wait(info->freeing);
	while (++iterate < philo_count)
		kill(pids[iterate], SIGQUIT);
	return (NULL);
}
