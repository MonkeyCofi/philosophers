/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:10:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/10 16:29:23 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	where_fork(t_single_philo *p)
{
	t_philos	*ph;

	ph = p->info;
	while (not_dead(ph))
	{
		if (left_fork_free(p))
			pick_up_left_fork(p);
		if (right_fork_free(p))
			pick_up_right_fork(p);
		if (left_fork_free(p) || right_fork_free(p))
			break ;
	}
}

void	philo_hungy(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
	where_fork(p);
	if (!left_fork_free(p) && !right_fork_free(p))
	{
		ft_usleep(info->time_to_eat);
		print_message(p->info, p, "is eating");
		pthread_mutex_lock(p->eating_mutex);
		p->meals_eaten++;
		p->last_meal = get_time_ms();
		pthread_mutex_unlock(p->eating_mutex);
		pthread_mutex_lock(p->left_fork);
		p->left_free = 1;
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_lock(p->right_fork);
		p->right_free = 1;
		pthread_mutex_unlock(p->right_fork);
	}
}

void	philo_eepy(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
	print_message(info, p, "is sleeping");
	ft_usleep(info->time_to_sleep);
}

void	*philo_routine(void *ptr)
{
	t_single_philo	*p;
	t_philos		*info;

	p = ptr;
	info = p->info;
	if (p->phil_id % 2)
		ft_usleep(info->time_to_die / 2);
	while (not_dead(info))
	{
		philo_hungy(p);
		pthread_mutex_lock(p->eating_mutex);
		if (p->meals_eaten == info->num_of_meals)
		{
			pthread_mutex_unlock(p->eating_mutex);
			break ;
		}
		pthread_mutex_unlock(p->eating_mutex);
		philo_eepy(p);
		print_message(info, p, "is thinking");
	}
	return (NULL);
}
