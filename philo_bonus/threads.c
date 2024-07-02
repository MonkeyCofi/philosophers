/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:26:38 by pipolint          #+#    #+#             */
/*   Updated: 2024/07/02 20:30:38 by pipolint         ###   ########.fr       */
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
	int				i;

	p = philo;
	info = p->info;
	i = -1;
	while (1)
	{
		check_meal_time(p);
		if (eaten_fully(info))
			break ;
		if (!not_dead(info))
		{
			sem_wait(info->writing);
			printf("%ld %d has died\n", get_time_ms() - info->start_time, p->phil_id);
			while (++i < info->num_of_philos)
				sem_post(info->freeing);
				//sem_post(info->send_kill);
			break ;
		}
		//usleep(250);
	}
	printf("exited philo monitor\n");
	return (NULL);
}

void	*all_eaten(void *philo_array)
{
	t_single_philo	*p;
	t_philos		*info;

	p = philo_array;
	info = p->info;
	sem_wait(info->finished);
	drop_right_fork(p);
	drop_left_fork(p);
	free(info->pids);
	free(p);
	exit(0);
}

void	*free_resources(void *philo_array)
{
	t_single_philo	*p;
	t_philos		*info;

	p = philo_array;
	info = p->info;
	sem_wait(info->freeing);
	free(info->pids);
	close_sems(info, p, 1);
	free(p);
	sem_post(info->send_kill);
	return (NULL);
}

//void	*kill_philosophers(void *philo_array)
//{
//	t_single_philo	*philos;
//	t_philos		*info;
//	int				philo_count;
//	int				iterate;
//	pid_t			*pids;

//	philos = philo_array;
//	info = philos->info;
//	philo_count = info->num_of_philos;
//	iterate = -1;
//	pids = info->pids;
//	sem_wait(info->send_kill);
//	while (++iterate < philo_count)
//		kill(pids[iterate], SIGKILL);
//	return (NULL);
//}

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
	pids = info->pids;
	iterate = -1;
	while (++iterate < philo_count)
		sem_wait(info->send_kill);
	iterate = -1;
	while (++iterate < philo_count)
		//kill(pids[iterate], SIGKILL);
		kill(pids[iterate], SIGINT);
	return (NULL);
}
