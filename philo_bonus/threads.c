/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:26:38 by pipolint          #+#    #+#             */
/*   Updated: 2024/07/06 19:04:44 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_print(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
	sem_wait(info->break_check);
	if (!info->printed)
	{
		sem_post(info->break_check);
		return (1);
	}
	sem_post(info->break_check);
	return (0);
}

int	should_break(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
	sem_wait(info->break_check);
	if (!not_dead(info) || info->end)
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
	info->printed = 1;
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
		return (1);
	if (!check_meal_time(p))
	{
		sem_wait(info->writing);
		if (should_print(p))
			printf("%ld %d has died\n", get_time_ms() - info->start_time, p->phil_id);
		while (++i < philo_count)
			sem_post(info->monitor_break);
		sem_post(info->writing);
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
		usleep(500);
	}
	return (NULL);
}
