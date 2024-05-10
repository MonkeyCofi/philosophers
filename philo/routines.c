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
<<<<<<< HEAD
	t_philos	*ph;
	//while (1)
	ph = p->info;
	while (not_dead(ph))
=======
	t_philos	*info;

	info = p->info;
	while (not_dead(info))
>>>>>>> main
	{
		if (p->left_free)
		{
			print_message(p->info, p, "has taken their left fork");
			pthread_mutex_lock(p->left_fork);
			p->left_free = 0;
		}
		if (p->right_free)
		{
			print_message(p->info, p, "has taken their right fork");
			pthread_mutex_lock(p->right_fork);
			p->right_free = 0;
		}
		if (!p->left_free || !p->right_free)
			break ;
	}
}

void	philo_hungy(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
<<<<<<< HEAD
	//if (not_dead(info))
	//	where_fork(p);
	where_fork(p);
	if (!p->left_free && !p->right_free)
=======
	where_fork(p);
	if (!p->left_free && !p->right_free && not_dead(info))
>>>>>>> main
	{
		print_message(p->info, p, "is eating");
		ft_usleep(info->time_to_eat);
		pthread_mutex_lock(p->eating_mutex);
		p->meals_eaten++;
		p->last_meal = get_time_ms();
		p->left_free = 1;
		p->right_free = 1;
		pthread_mutex_unlock(p->eating_mutex);
	}
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
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
