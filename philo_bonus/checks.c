/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:45:31 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/08 17:27:39 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_meals_eaten(t_single_philo *philo)
{
	sem_wait(philo->eating);
	if (philo->meals_eaten == ((t_philos *)philo->info)->num_of_meals)
	{
		((t_philos *)philo->info)->all_eaten = 1;
		sem_post(philo->eating);
		return (1);
	}
	sem_post(philo->eating);
	return (0);
}

int	check_meal_time(t_single_philo *philo)
{
	sem_wait(philo->eating);
	if (get_time_ms() >= philo->last_meal + ((t_philos *)philo->info)->time_to_die)
	{
		printf("Philo %d is dead\n", philo->phil_id);
		*philo->is_dead = 1;
		return (0);
	}
	sem_post(philo->eating);
	return (1);
}

int	kill_philos(t_philos *p, pid_t *pids)
{
	int	i;

	i = -1;
	sem_wait(p->eating);
	if (p->all_eaten || p->dead)
	{
		while (++i < p->num_of_philos)
		{
			sem_close(p->forks);
			printf("Sending SIGQUIT signal to Philosopher %d with id: %d\n", i + 1, pids[i]);
			kill(pids[i], SIGQUIT);
		}
	}
	sem_post(p->eating);
	return (1);
}
