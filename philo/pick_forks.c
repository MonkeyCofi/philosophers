/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:11:24 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/24 17:54:13 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_left_fork(t_single_philo *p)
{
	while (not_dead(p->info))
	{
		if (!left_fork_free(p))
			continue ;
		else
			break ;
	}
	print_message(p->info, p, "has taken a fork");
	pthread_mutex_lock(p->left_fork);
	*p->left_free = 0;
	pthread_mutex_unlock(p->left_fork);
	return (1);
}

int	pick_right_fork(t_single_philo *p)
{
	while (not_dead(p->info))
	{
		if (!right_fork_free(p))
			continue ;
		else
			break ;
	}
	print_message(p->info, p, "has taken a fork");
	pthread_mutex_lock(p->right_fork);
	*p->right_free = 0;
	pthread_mutex_unlock(p->right_fork);
	return (1);
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
