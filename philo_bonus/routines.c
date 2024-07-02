/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:02:26 by pipolint          #+#    #+#             */
/*   Updated: 2024/07/02 20:21:32 by pipolint         ###   ########.fr       */
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

int	philo_routine(t_single_philo *philo, t_single_philo	*philo_array)
{
	pthread_t	monitor;
	pthread_t	meals;
	pthread_t	freer;

	if (pthread_create(&monitor, NULL, philo_monitor, philo) == -1)
		return (-1);
	if (pthread_create(&freer, NULL, free_resources, philo_array) == -1)
		return (-1);
	if (((t_philos *)philo->info)->num_of_meals > 0)
	{
		if (pthread_create(&meals, NULL, all_eaten, philo_array) == -1)
			return (-1);
	}
	if (philo->phil_id % 2 == 0)
		ft_usleep(((t_philos *)philo->info)->time_to_eat / 2);
	while (1)
	{
		eating(philo);
		if (all_meals_eaten(philo) || !not_dead(philo->info))
		{
			sem_post(((t_philos *)philo->info)->finished);
			//ft_usleep(((t_philos *)philo->info)->time_to_eat);
			break ;
		}
		sleeping(philo);
		thinking(philo);
	}
	printf("exited routine\n");
	if (((t_philos *)philo->info)->num_of_meals > 0)
		pthread_join(meals, NULL);
	pthread_join(freer, NULL);
	pthread_join(monitor, NULL);
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
