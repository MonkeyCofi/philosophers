/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:00:10 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/05 16:02:09 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_left_fork(t_single_philo *philo)
{
	sem_wait(((t_philos *)philo->info)->forks);
	philo->has_left = 1;
	print_message(philo->info, philo, "has taken their left fork");
	return (1);
}

int	take_right_fork(t_single_philo *philo)
{
	sem_wait(((t_philos *)philo->info)->forks);
	philo->has_right = 1;
	print_message(philo->info, philo, "has taken their right fork");
	return (1);
}

int	take_forks(t_single_philo *philo)
{
	if (take_left_fork(philo) && take_right_fork(philo))
		return (1);
	return (0);
}

int	drop_left_fork(t_single_philo *philo)
{
	philo->has_left = 0;
	print_message(philo->info, philo, "has dropped their left fork");
	sem_post(((t_philos *)philo->info)->forks);
	return (1);
}

int	drop_right_fork(t_single_philo *philo)
{
	philo->has_right = 0;
	print_message(philo->info, philo, "has dropped their right fork");
	sem_post(((t_philos *)philo->info)->forks);
	return (1);
}
