/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:11:24 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/21 15:41:50 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	drop_forks(t_single_philo *p)
{
	pthread_mutex_lock(p->right_fork);
	if (!(*p->right_free))
	{
		*p->right_free = 1;
		pthread_mutex_unlock(p->right_fork);
	}
	else
		pthread_mutex_unlock(p->right_fork);
	pthread_mutex_lock(p->left_fork);
	if (!(*p->left_free))
	{
		*p->left_free = 1;
		pthread_mutex_unlock(p->left_fork);
	}
	else
		pthread_mutex_unlock(p->left_fork);
	return (0);
}

int	left_fork_free(t_single_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	if (*p->left_free)
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
	if (*p->right_free)
	{
		pthread_mutex_unlock(p->right_fork);
		return (1);
	}
	pthread_mutex_unlock(p->right_fork);
	return (0);
}

int	pick_left_fork(t_single_philo *p)
{
	if (left_fork_free(p))
	{
		pthread_mutex_lock(p->left_fork);
		print_message(p->info, p, "has picked up their left fork");
		*p->left_free = 0;
		pthread_mutex_unlock(p->left_fork);
		return (1);
	}
	return (0);
}

int	pick_right_fork(t_single_philo *p)
{
	if (right_fork_free(p))
	{
		pthread_mutex_lock(p->right_fork);
		print_message(p->info, p, "has picked up their right fork");
		*p->right_free = 0;
		pthread_mutex_unlock(p->right_fork);
		return (1);
	}
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
	}
	return (0);
}