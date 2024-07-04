/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:26:38 by pipolint          #+#    #+#             */
/*   Updated: 2024/07/04 21:45:12 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_break(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
	sem_wait(info->break_check);
	if (info->end || !not_dead(info))
	{
		sem_post(info->break_check);
		return (1);
	}
	sem_post(info->break_check);
	return (0);
}

void	*increment(void *philo)
{
	t_single_philo	*p;
	t_philos		*info;

	p = philo;
	info = p->info;
	sem_wait(info->monitor_break);
	sem_wait(info->break_check);
	info->end = 1;
	sem_post(info->break_check);
	sem_post(info->meals);
	return (NULL);
}

int	death(t_single_philo *p)
{
	t_philos	*info;
	int			philo_count;
	int			i;

	info = p->info;
	i = -1;
	philo_count = info->num_of_philos;
	if (should_break(p))
	{
		return (1);
	}
	if (!check_meal_time(p))
	{
		sem_wait(info->writing);
		printf("%ld %d has died\n", get_time_ms() - info->start_time, p->phil_id);
		sem_post(info->writing);
		while (++i < philo_count)
			sem_post(info->monitor_break);
		return (1);
	}
	return (0);
}

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
		if (death(p))
			break ;
		if (eaten_fully(info))
		{
			sem_post(info->meals);
			break ;
		}
	}
	return (NULL);
}

void	*free_resources(void *philo_array)
{
	t_single_philo	*philos;
	t_philos		*info;

	philos = philo_array;
	info = philos->info;
	sem_wait(info->freeing);
	drop_right_fork(philos);
	drop_left_fork(philos);
	close_sems(info, philos, 1);
	pthread_join(info->freeing_thread, NULL);
	pthread_join(info->incrementor, NULL);
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
//	iterate = -1;
//	while (++iterate < philo_count)
//	{
//		printf("received signal %d times\n", iterate + 1);
//		sem_wait(info->send_kill);
//		usleep(250);
//	}
//	iterate = -1;
//	while (++iterate < philo_count)
//	{
//		//printf("killed %d times\n", iterate + 1);
//		kill(pids[iterate], SIGINT);
//	}
//	return (NULL);
//}
