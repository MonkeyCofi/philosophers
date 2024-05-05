/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:10:08 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/03 19:10:25 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_devour(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
	if (p->left_free)
	{
		p->left_free = 0;
		print_message(p->info, p, "has taken a fork");
		pthread_mutex_lock(p->left_fork);
	}
	if (p->right_free)
	{
		p->right_free = 0;
		print_message(p->info, p, "has taken a fork");
		pthread_mutex_lock(p->right_fork);
	}
	print_message(p->info, p, "is eating");
	ft_usleep(info->time_to_eat);
	p->last_meal = get_time_ms();
	p->left_free = 1;
	p->right_free = 1;
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void	philo_eepy(t_single_philo *p)
{
	t_philos	*info;

	info = p->info;
	print_message(info, p, "is sleeping");
	ft_usleep(info->time_to_sleep);
}