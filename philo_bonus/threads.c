/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:26:38 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/08 17:48:31 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test(void *philo)
{
	t_single_philo	*p;
	t_philos		*info;

	p = (t_single_philo *)philo;
	info = p->info;
	sem_wait(info->test_sem);
	return (NULL);
}

void	*monitor(void *philo)
{
	t_single_philo	*p;

	p = (t_single_philo *)philo;
	while (1)
	{
		if (!check_meal_time(philo))
		{
			sem_post(((t_philos *)p->info)->test_sem);
			break ;
		}
	}
	return (NULL);
}
