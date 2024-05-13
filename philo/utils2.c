/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:38:15 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/13 16:34:11 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_meal_time(t_philos *p, int i)
{
	pthread_mutex_lock(&p->eating_mutex);
	if (get_time_ms() > p->philosophers[i].last_meal + p->time_to_die)
	{
		*p->philosophers[i].is_dead = 1;
		pthread_mutex_lock(p->philosophers[i].write_lock);
		printf("%ld %d has died\n", get_time_ms() - p->start_time, p->philosophers[i].phil_id);
		pthread_mutex_unlock(p->philosophers[i].write_lock);
	}
	pthread_mutex_unlock(&p->eating_mutex);
}

int	pick_left_fork(t_single_philo *ph)
{
	t_philos	*p;

	p = ph->info;
	if (left_fork_free(ph))
	{
		pthread_mutex_lock(ph->left_fork);
		print_message(p, ph, "has picked up their left fork");
		ph->left_free = 0;
		pthread_mutex_unlock(ph->left_fork);
		return (1);
	}
	return (0);
}

int	pick_right_fork(t_single_philo *ph)
{
	t_philos	*p;

	p = ph->info;
	if (right_fork_free(ph))
	{
		pthread_mutex_lock(ph->right_fork);
		print_message(p, ph, "has picked up their right fork");
		ph->right_fork = 0;
		pthread_mutex_unlock(ph->right_fork);
		return (1);
	}
	return (0);
	
}

int	left_fork_free(t_single_philo *ph)
{
	pthread_mutex_lock(ph->left_fork);
	if (ph->left_free)
	{
		pthread_mutex_unlock(ph->left_fork);
		return (1);
	}
	pthread_mutex_unlock(ph->left_fork);
	return (0);
}

int	right_fork_free(t_single_philo *ph)
{
	pthread_mutex_lock(ph->right_fork);
	if (ph->right_free)
	{
		pthread_mutex_unlock(ph->right_fork);
		return (1);
	}
	pthread_mutex_unlock(ph->right_fork);
	return (0);
}

// int	scan_and_lock_forks(t_single_philo *p)
// {
// 	t_philos	*info;

// 	info = p->info;
// 	if (pthread_mutex_lock(p->left_fork) == -1)
// 		return (-1);
// 	if (p->left_free)
// 	{
// 		p->left_free = 0;
// 		print_message(info, p, "has taken their left fork");
// 	}
// 	if (pthread_mutex_unlock(p->left_fork) == -1)
// 		return (-1);
// 	if (pthread_mutex_lock(p->right_fork) == -1)
// 		return (-1);
// 	if (p->right_free)
// 	{
// 		p->right_free = 0;
// 		print_message(info, p, "has taken their right fork");
// 	}
// 	if (pthread_mutex_unlock(p->right_fork) == -1)
// 		return (-1);
// 	return (1);
// }
