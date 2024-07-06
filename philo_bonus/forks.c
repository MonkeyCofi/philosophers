/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:00:10 by pipolint          #+#    #+#             */
/*   Updated: 2024/07/06 15:27:54 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_left_fork(t_single_philo *philo)
{
	sem_wait(((t_philos *)philo->info)->forks);
	print_message(philo->info, philo, "has taken a fork");
	return (1);
}

int	take_right_fork(t_single_philo *philo)
{
	sem_wait(((t_philos *)philo->info)->forks);
	print_message(philo->info, philo, "has taken a fork");
	return (1);
}

int	take_forks(t_single_philo *philo)
{
	take_left_fork(philo);
	take_right_fork(philo);
	return (1);
}

int	drop_left_fork(t_single_philo *philo)
{
	sem_post(((t_philos *)philo->info)->forks);
	return (1);
}

int	drop_right_fork(t_single_philo *philo)
{
	sem_post(((t_philos *)philo->info)->forks);
	return (1);
}
