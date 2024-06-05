/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:45:31 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/05 16:47:41 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_meals_eaten(t_single_philo *philo)
{
	sem_wait(philo->eating);
	if (philo->meals_eaten == ((t_philos *)philo->info)->num_of_meals)
	{
		sem_post(philo->eating);
		return (1);
	}
	sem_post(philo->eating);
	return (0);
}

int	check_meal_time(t_single_philo *philo)
{
	sem_wait(philo->eating);
	if (get_time_ms() - ((t_philos *)philo->info)->start_time >= philo->last_meal - ((t_philos *)philo->info)->time_to_die)
		*philo->is_dead = 1;
	sem_post(philo->eating);
	return (1);
}

int	kill_philos(t_single_philo *philos, pid_t *pids)
{
	int	i;

	i = -1;
	sem_wait(((t_philos *)philos->info)->eating);
	(void)pids;
	return (1);
}