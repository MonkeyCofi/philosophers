/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:38:15 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/10 16:58:28 by pipolint         ###   ########.fr       */
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

int	pick_up_left_fork(t_single_philo *p)
{
	t_philos	*ph;

	ph = p->info;
	if (left_fork_free(p))
	{
		pthread_mutex_lock(p->left_fork);
		print_message(ph, p, "has taken their left fork");
		p->left_free = 0;
		pthread_mutex_unlock(p->left_fork);
	}
	return (1);
}

int	pick_up_right_fork(t_single_philo *p)
{
	t_philos	*ph;

	ph = p->info;
	if (right_fork_free(p))
	{
		pthread_mutex_lock(p->right_fork);
		print_message(ph, p, "has taken their right fork");
		p->right_free = 0;
		pthread_mutex_unlock(p->right_fork);
	}
	return (1);

}

int	left_fork_free(t_single_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	if (p->left_free)
	{
		pthread_mutex_unlock(p->left_fork);
		return (1);
	}
	pthread_mutex_unlock(p->left_fork);
	return (0);
}

int	right_fork_free(t_single_philo *p)
{
	pthread_mutex_lock(p->right_fork);
	if (p->right_free)
	{
		pthread_mutex_unlock(p->right_fork);
		return (1);
	}
	pthread_mutex_unlock(p->right_fork);
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
