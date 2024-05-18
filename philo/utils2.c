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
	while (not_dead(p))
	{
		if (!left_fork_free(ph))
			ft_usleep(50);
		else
			break ;
	}
	pthread_mutex_lock(ph->left_fork);
	ph->left_free = 0;
	pthread_mutex_unlock(ph->left_fork);
	print_message(p, ph, "has picked up their left fork");
	return (1);
	
	// if (left_fork_free(ph))
	// {
	// 	pthread_mutex_lock(ph->left_fork);
	// 	ph->left_free = 0;
	// 	pthread_mutex_unlock(ph->left_fork);
	// 	print_message(p, ph, "has picked up their left fork");
	// 	return (1);
	// }
	return (0);
}

int	pick_right_fork(t_single_philo *ph)
{
	t_philos	*p;

	p = ph->info;
	while (not_dead(p))
	{
		if (!right_fork_free(ph))
			ft_usleep(50);
		else
			break ;
	}
	pthread_mutex_lock(ph->right_fork);
	ph->right_free = 0;
	pthread_mutex_unlock(ph->right_fork);
	print_message(p, ph, "has picked up their right fork");
	return (1);
	// t_philos	*p;

	// p = ph->info;
	// if (right_fork_free(ph))
	// {
	// 	pthread_mutex_lock(ph->right_fork);
	// 	ph->right_free = 0;
	// 	pthread_mutex_unlock(ph->right_fork);
	// 	print_message(p, ph, "has picked up their right fork");
	// 	return (1);
	// }
	// return (0);
	
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
