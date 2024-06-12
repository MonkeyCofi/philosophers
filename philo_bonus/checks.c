/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:45:31 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/12 18:38:31 by pipolint         ###   ########.fr       */
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

void	set_dead(t_single_philo *philo)
{
	sem_wait(philo->dead);
	*philo->is_dead = 1;
	sem_post(philo->dead);
}

void	set_all_dead(t_single_philo *p)
{
	t_philos	*info;
	int			counter;

	counter = -1;
	info = p->info;
	sem_wait(p->dead);
	while (++counter < info->num_of_philos)
		p[counter].end = 1;
	sem_post(p->dead);
}

int	check_meal_time(t_single_philo *philo)
{
	sem_wait(philo->eating);
	if (get_time_ms() >= philo->last_meal + ((t_philos *)philo->info)->time_to_die)
	{
		sem_post(philo->eating);
		set_dead(philo);
		sem_wait(philo->writing);
		printf("%ld %d has died\n", get_time_ms() - ((t_philos *)philo->info)->start_time, philo->phil_id);
		sem_post(philo->writing);
		return (0);
	}
	sem_post(philo->eating);
	return (1);
}
