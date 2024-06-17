/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_drop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwubuntu <uwubuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:59:45 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/17 13:53:33 by uwubuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	drop_forks(t_single_philo *p)
{
	drop_right_fork(p);
	drop_left_fork(p);
	return (0);
}

int	drop_left_fork(t_single_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	*p->left_free = 1;
	pthread_mutex_unlock(p->left_fork);
	return (0);
}

int	drop_right_fork(t_single_philo *p)
{
	pthread_mutex_lock(p->right_fork);
	*p->right_free = 1;
	pthread_mutex_unlock(p->right_fork);
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
