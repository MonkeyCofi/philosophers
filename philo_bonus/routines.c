/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:02:26 by pipolint          #+#    #+#             */
/*   Updated: 2024/07/04 12:06:20 by pipolint         ###   ########.fr       */
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
	t_philos	*info;
	//pthread_t	freeing;
	//pthread_t	incrementor;

	info = philo->info;
	if (pthread_create(&monitor, NULL, philo_monitor, philo) == -1)
		return (-1);
	//if (pthread_create(&info->freeing_thread, NULL, free_resources, philo_array) == -1)
	//	return (-1);
	if (pthread_create(&info->incrementor, NULL, increment, philo) == -1)
		return (-1);
	if (philo->phil_id % 2 == 0)
		ft_usleep(((t_philos *)philo->info)->time_to_eat / 2);
	while (!should_break(philo))
	{
		eating(philo);
		//if (should_break(philo))
		//{
		//	printf("breaking\n");
		//	break ;
		//}
		if (all_meals_eaten(philo))
		{
			//printf("philosopher %d has eaten all their eals\n", philo->phil_id);
			drop_right_fork(philo);
			drop_left_fork(philo);
			break ;
		}
		sleeping(philo);
		thinking(philo);
	}
	pthread_join(monitor, NULL);
	pthread_join(info->incrementor, NULL);
	close_sems(philo->info, philo, 1);
	(void)philo_array;
	//printf("exiting successfully\n");
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
