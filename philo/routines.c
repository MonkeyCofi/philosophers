/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwubuntu <uwubuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:10:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/17 20:08:32 by uwubuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *ptr)
{
	t_single_philo	*p;

	p = ptr;
	if (p->phil_id % 2 && ((t_philos *)p->info)->num_of_philos > 1)
		ft_usleep(((t_philos *)p->info)->time_to_eat / 2);
	while (1)
	{
		if (!eating_preparation(p))
			break ;
		if (!not_dead(p->info))
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
		if (!left_fork_free(p))
			return (drop_left_fork(p));
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

int	eating(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
	print_message(info, p, "is eating");
	pthread_mutex_lock(p->eating_mutex);
	p->meals_eaten++;
	p->last_meal = get_time_ms();
	pthread_mutex_unlock(p->eating_mutex);
	printf("philo %d started usleeping at %ld\n", p->phil_id, get_time_ms() - info->start_time);
	ft_usleep(info->time_to_eat);
	printf("phillo %d Finished usleeping at %ld\n", p->phil_id, get_time_ms() - info->start_time);
	// usleep(info->time_to_eat);
	return (1);
}
