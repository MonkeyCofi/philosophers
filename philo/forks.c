/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:11:24 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/18 20:57:51 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	drop_forks(t_single_philo *p)
{
	t_philos	*ph;

	ph = p->info;
	pthread_mutex_lock(p->left_fork);
	if (!p->left_free)
	{
		p->left_free = 1;
		print_message(ph, p, "has dropped their left fork"); 
	}
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_lock(p->right_fork);
	if (!p->right_free)
	{
		p->right_free = 1;
		print_message(ph, p, "has dropped their right fork"); 
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
	int	left_picked;
	int	right_picked;

	left_picked = 0;
	right_picked = 0;
	if (pick_left_fork(p))
		left_picked = 1;
	if (left_picked && pick_right_fork(p))
		right_picked = 1;
	if (left_picked && right_picked)
		return (1);
	else if ((left_picked && !right_picked) || (!left_picked && right_picked))
		return (drop_forks(p));
	return (0);
}

// int	pick_forks(t_single_philo *p)
// {
// 	int	left;
// 	int	right;

// 	left = 0;
// 	right = 0;
// 	pthread_mutex_lock(p->left_fork);
// 	if (p->left_free)
// 	{
// 		p->left_free = 0;
// 		left = 1;
// 		print_message(p->info, p, "has picked up their left fork");
// 	}
// 	pthread_mutex_unlock(p->left_fork);
// 	if (!left)
// 		return (0);
// 	pthread_mutex_lock(p->right_fork);
// 	if (p->right_free)
// 	{
// 		p->right_free = 0;
// 		right = 1;
// 		print_message(p->info, p, "has picked up their right fork");	
// 	}
// 	pthread_mutex_unlock(p->right_fork);
// 	if (!right)
// 	{
// 		pthread_mutex_lock(p->left_fork);
// 		p->left_free = 1;
// 		pthread_mutex_unlock(p->left_fork);
// 		return (0);
// 	}
// 	return (1);
// 	//left = pick_left_fork(p);
// 	//right = pick_right_fork(p);
// 	//if (left && !right)
// 	//{
// 	//	pthread_mutex_lock(p->left_fork);
// 	//	p->left_free = 1;
// 	//	pthread_mutex_unlock(p->left_fork);
// 	//}
// 	//if (right && !left)
// 	//{
// 	//	pthread_mutex_lock(p->right_fork);
// 	//	p->right_free = 1;
// 	//	pthread_mutex_unlock(p->right_fork);
// 	//}
// 	return (1);
// }