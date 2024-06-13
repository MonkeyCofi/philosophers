/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:10:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/13 20:59:31 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *ptr)
{
	t_single_philo	*p;

	p = ptr;
	if (p->phil_id % 2 && p->meals_eaten == 0)
		ft_usleep(((t_philos *)p->info)->time_to_eat / 2);
	while (not_dead(p->info))
	{
		if (!eating_preparation(p))
			break ;
		sleeping(p);
		thinking(p);
	}
	printf("broke out\n");
	return (NULL);
}

int	eating_preparation(t_single_philo *p)
{
	if (!fully_devoured(p) && not_dead(p->info))
	{
		if (pick_forks(p))
		{
			eating(p);
			return (1);
		}
		return (0);
	}
	return (0);
}

void	sleeping(t_single_philo *p)
{
	print_message(p->info, p, "is sleeping");
	drop_forks(p);
	ft_usleep(((t_philos *)p->info)->time_to_sleep);
}

void	thinking(t_single_philo *p)
{
	print_message(p->info, p, "is thinking");
}

void	eating(t_single_philo *p)
{
	print_message(p->info, p, "is eating");
	pthread_mutex_lock(p->eating_mutex);
	p->last_meal = get_time_ms();
	p->meals_eaten++;
	pthread_mutex_unlock(p->eating_mutex);
	ft_usleep(((t_philos *)p->info)->time_to_eat);
}
