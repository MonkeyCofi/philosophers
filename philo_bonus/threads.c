/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:26:38 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/10 21:57:46 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//void	*test(void *philo)
//{
//	t_single_philo	*p;
//	t_philos		*info;

//	p = philo;
//	info = p->info;
//	while (1)
//	{
//		sem_wait(info->test_sem);
//		sem_post(info->test_sem);
//		break ;
//	}
//	exit(EXIT_SUCCESS);
//}

//void	*monitor(void *philo)
//{
//	t_single_philo	*p;

//	p = (t_single_philo *)philo;
//	while (1)
//	{
//		if (!not_dead(p->info))
//		{
//			//sem_post(((t_philos *)&p[i].info)->test_sem);
//			sem_post(((t_philos *)p->info)->test_sem);
//			break ;
//		}
//	}
//	set_all_dead(p);
//	return (NULL);
//}

void	*test(void *philo)
{
	t_single_philo	*p;
	t_philos		*info;

	p = philo;
	info = p->info;
	while (1)
	{
		sem_wait(info->test_sem);
		break ;
	}
	exit(EXIT_SUCCESS);
}

void	*monitor(void *philo)
{
	t_single_philo	*p;
	t_philos		*info;
	int				count;

	p = philo;
	count = 0;
	info = p->info;
	while (1)
	{
		if (count == info->num_of_philos - 1)
			count = 0;
		if (!check_meal_time(&p[count]))
			sem_post(info->test_sem);
		count++;
	}
	return (NULL);
}

void	*freeing(void *philos)
{
	t_single_philo	*p;
	t_philos		*info;
	int				count;

	p = philos;
	info = p->info;
	count = 0;
	while (1)
	{
		if (!not_dead(info))
		{
			while (count < (info->num_of_philos))
			{
				count++;
				//kill(info->pids[count++], SIGKILL);
			}
			break ;
		}
	}
	return (NULL);
}
