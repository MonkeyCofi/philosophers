/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:26:38 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/10 00:48:40 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test(void *philo)
{
	t_single_philo	*p;

	p = philo;
	sem_wait(((t_philos *)p->info)->test_sem);
	exit(EXIT_SUCCESS);
}

void	*monitor(void *philo)
{
	t_single_philo	*p;

	p = (t_single_philo *)philo;
	while (1)
	{
		if (!check_meal_time(philo) || all_meals_eaten(p))
		{
			sem_post(((t_philos *)p->info)->test_sem);
			break ;
		}
	}
	return (NULL);
}
