/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:45:31 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/14 18:47:12 by pipolint         ###   ########.fr       */
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

int	eaten_fully(t_philos *info)
{
	sem_wait(info->eating);
	if (info->all_eaten)
	{
		sem_post(info->eating);
		return (1);
	}
	sem_post(info->eating);
	return (0);
}

int	check_meal_time(t_single_philo *philo)
{
	sem_wait(philo->eating);
	if (get_time_ms() >= philo->last_meal + ((t_philos *)philo->info)->time_to_die)
	{
		set_dead(philo);
		sem_post(philo->eating);
		return (0);
	}
	sem_post(philo->eating);
	return (1);
}

int	not_dead(t_philos *p)
{
	sem_wait(p->dead_sem);
	if (p->dead)
	{
		sem_post(p->dead_sem);
		return (0);
	}
	sem_post(p->dead_sem);
	return (1);
}
