/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:02:26 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/10 21:40:11 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ended(t_single_philo *p)
{
	sem_wait(p->ended);
	if (p->end)
	{
		sem_post(p->ended);
		return (1);
	}
	sem_post(p->ended);
	return (0);
}

int	philo_routine(t_single_philo *philo)
{
	pthread_create(&philo->monitor, NULL, test, philo);
	while (1)
	{
		if (!not_dead(philo->info))
			break ;
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	pthread_join(philo->monitor, NULL);
	close_sems(philo);
	return (1);
}

int	thinking(t_single_philo *philo)
{
	print_message(philo->info, philo, "is thinking");
	return (1);
}

int	eating(t_single_philo *philo)
{
	if (!take_forks(philo))
		return (0);
	print_message(philo->info, philo, "is eating");
	sem_wait(philo->eating);
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	sem_post(philo->eating);
	ft_usleep(((t_philos *)philo->info)->time_to_eat);
	return (1);
}

int	sleeping(t_single_philo *philo)
{
	drop_right_fork(philo);
	drop_left_fork(philo);
	print_message(philo->info, philo, "is sleeping");
	ft_usleep(((t_philos *)philo->info)->time_to_sleep);
	return (1);
}
