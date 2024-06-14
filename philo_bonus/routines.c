/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:02:26 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/14 18:46:32 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_ended(t_single_philo *p)
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
	if (philo->phil_id % 2 == 0)
		ft_usleep(((t_philos *)philo->info)->time_to_eat / 2);
	pthread_create(&philo->monitor, NULL, philo_monitor, philo);
	while (1)
	{
		eating(philo);
		if (all_meals_eaten(philo))
		{
			drop_right_fork(philo);
			drop_left_fork(philo);
			break ;
		}
		sleeping(philo);
		thinking(philo);
	}
	pthread_join(philo->monitor, NULL);
	close_sems(philo->info, philo);
	exit(EXIT_SUCCESS);
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
	sem_wait(philo->eating);
	print_message(philo->info, philo, "is eating");
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	sem_post(philo->eating);
	ft_usleep(((t_philos *)philo->info)->time_to_eat);
	return (1);
}

int	sleeping(t_single_philo *philo)
{
	print_message(philo->info, philo, "is sleeping");
	drop_right_fork(philo);
	drop_left_fork(philo);
	ft_usleep(((t_philos *)philo->info)->time_to_sleep);
	return (1);
}
