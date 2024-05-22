/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:10:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/22 16:19:28 by pipolint         ###   ########.fr       */
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
		if (!philo_hungy(p))
			break ;
		philo_eepy(p);
		philo_thinky(p);
	}
	return (NULL);
}

int	philo_hungy(t_single_philo *p)
{
	if (!fully_devoured(p))
	{
		if (pick_forks(p))
			philo_devour(p);
		return (1);
	}
	return (0);
}

void	philo_eepy(t_single_philo *p)
{
	print_message(p->info, p, "is sleeping");
	drop_forks(p);
	ft_usleep(((t_philos *)p->info)->time_to_sleep);
}

void	philo_thinky(t_single_philo *p)
{
	print_message(p->info, p, "is thinking");
}

void	philo_devour(t_single_philo *p)
{
	print_message(p->info, p, "is eating");
	pthread_mutex_lock(p->eating_mutex);
	p->last_meal = get_time_ms();
	p->meals_eaten++;
	pthread_mutex_unlock(p->eating_mutex);
	ft_usleep(((t_philos *)p->info)->time_to_eat);
}
