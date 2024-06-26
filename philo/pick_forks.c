/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:11:24 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/26 16:13:16 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_left_fork(t_single_philo *p)
{
	while (!left_fork_free(p))
		usleep(100);
	pthread_mutex_lock(p->left_fork);
	*p->left_free = 0;
	pthread_mutex_unlock(p->left_fork);
	if (!not_dead(p->info))
		return (drop_left_fork(p));
	print_message(p->info, p, "has taken a fork");
	return (1);
}

int	pick_right_fork(t_single_philo *p)
{
	while (!right_fork_free(p))
		usleep(100);
	pthread_mutex_lock(p->right_fork);
	*p->right_free = 0;
	pthread_mutex_unlock(p->right_fork);
	if (!not_dead(p->info))
		return (drop_right_fork(p));
	print_message(p->info, p, "has taken a fork");
	return (1);
}

int	pick_forks(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
	if (!pick_left_fork(p))
		return (0);
	if (info->num_of_philos <= 1)
		return (drop_left_fork(p));
	if (!pick_right_fork(p))
		return (drop_left_fork(p));
	(void)info;
	return (1);
}
