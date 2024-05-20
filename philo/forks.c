/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:11:24 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/20 16:17:39 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	drop_forks(t_single_philo *p)
{
	pthread_mutex_lock(p->right_fork);
	if (!p->right_free)
	{
		p->right_free = 1;
		pthread_mutex_unlock(p->right_fork);
	}
	else
		pthread_mutex_unlock(p->right_fork);
	pthread_mutex_lock(p->left_fork);
	if (!p->left_free)
	{
		p->left_free = 1;
		pthread_mutex_unlock(p->left_fork);
	}
	else
		pthread_mutex_unlock(p->left_fork);
	return (0);
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

int	pick_left_fork(t_single_philo *p)
{
	t_philos	*ph;

	ph = p->info;
	pthread_mutex_lock(p->left_fork);
	if (p->left_free)
	{
		p->left_free = 0;
		print_message(ph, p, "has taken their left fork");
		pthread_mutex_unlock(p->left_fork);
		return (1);
	}
	pthread_mutex_unlock(p->left_fork);
	return (0);
}

int	pick_right_fork(t_single_philo *p)
{
	t_philos	*ph;

	ph = p->info;
	pthread_mutex_lock(p->right_fork);
	if (p->right_free)
	{
		p->right_free = 0;
		print_message(ph, p, "has taken their right fork");
		pthread_mutex_unlock(p->right_fork);
		return (1);
	}
	pthread_mutex_unlock(p->right_fork);
	return (0);
}

int	pick_forks(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
	while (not_dead(info))
	{
		if (pick_left_fork(p))
		{
			if (pick_right_fork(p))
				return (1);
		}
		else
			drop_forks(p);
	}
	return (0);
}
