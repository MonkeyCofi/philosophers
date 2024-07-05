/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:10:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/07/04 11:35:09 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *ptr)
{
	t_single_philo	*p;
	t_philos		*info;

	p = ptr;
	info = p->info;
	if (p->phil_id % 2 && ((t_philos *)p->info)->num_of_philos > 1)
		ft_usleep(((t_philos *)p->info)->time_to_eat / 2, info);
	while (1)
	{
		if (!eating_preparation(p))
			break ;
		if (!not_dead(info))
		{
			drop_forks(p);			
			break ;
		}
		sleeping(p);
		thinking(p);
	}
	return (NULL);
}

int	eating_preparation(t_single_philo *p)
{
	if (!fully_devoured(p))
	{
		if (pick_forks(p))
			return (eating(p));
		return (0);
	}
	return (0);
}

void	sleeping(t_single_philo *p)
{
	print_message(p->info, p, "is sleeping");
	drop_forks(p);
	ft_usleep(((t_philos *)p->info)->time_to_sleep, p->info);
}

void	thinking(t_single_philo *p)
{
	print_message(p->info, p, "is thinking");
}

int	eating(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
	print_message(info, p, "is eating");
	pthread_mutex_lock(p->eating_mutex);
	p->meals_eaten++;
	p->last_meal = get_time_ms();
	pthread_mutex_unlock(p->eating_mutex);
	ft_usleep(info->time_to_eat, info);
	return (1);
}
