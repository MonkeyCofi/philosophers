/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:02:26 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/28 20:18:11 by pipolint         ###   ########.fr       */
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
	pthread_t	term;
	pthread_t	monitor;
	pthread_t	meals;

	if (philo->phil_id % 2 == 0)
		ft_usleep(((t_philos *)philo->info)->time_to_eat / 2);
	pthread_create(&monitor, NULL, philo_monitor, philo);
	pthread_create(&term, NULL, detect_termination, philo_array);
	pthread_create(&meals, NULL, meal_thread, philo_array);
	while (1)
	{
		eating(philo);
		if (ended(philo))
			break ;
		if (all_meals_eaten(philo))
		{
			drop_right_fork(philo);
			drop_left_fork(philo);
			break ;
		}
		sleeping(philo);
		thinking(philo);
	}
	pthread_join(meals, NULL);
	//printf("joining meals thread\n");
	pthread_join(term, NULL);
	//printf("joining termination thread\n");
	pthread_join(monitor, NULL);
	//printf("joining monitoring thread\n");
	sem_post(philo->writing);
	close_sems(philo->info, philo, 1);
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
