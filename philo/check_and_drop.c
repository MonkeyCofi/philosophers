/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_drop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:59:45 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/14 13:10:51 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	drop_forks(t_single_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	if (!(*p->left_free))
		*p->left_free = 1;
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_lock(p->right_fork);
	if (!(*p->right_free))
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
