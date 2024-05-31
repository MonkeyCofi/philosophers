/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:47:17 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/31 21:02:20 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_routine(t_single_philo *philos)
{
	while (1)
	{
		if (not_dead(philos->info))
			break ;
	}
	return (1);
}

int	set_semaphores(t_philos *p, t_single_philo *philo)
{
	p->forks = sem_open("/forks", O_CREAT, 0644, p->num_of_philos);
	if (p->forks == SEM_FAILED)
		return (-1);
	p->dead_sem = sem_open("/dead_sem", O_CREAT, 0644, 1);
	if (p->dead_sem == SEM_FAILED)
		return (-1);
	p->writing = sem_open("/writing", O_CREAT, 0644, 1);
	if (p->writing == SEM_FAILED)
		return (-1);
}

int	init_philos(t_philos *p, t_single_philo *philos)
{
	int	count;

	count = -1;
	while (++count < p->num_of_philos)
	{
		philos[count].phil_id = count + 1;
		philos[count].info = p;
		philos[count].pid = fork();
		if (philos[count].pid == 0)
		{
			return (philo_routine(&philos[count]));
		}
		printf("Philo %d's pid: %d\n", philos[count].phil_id, philos[count].pid);
	}
	return (1);
}

int	get_info(t_philos *p, int ac, char **av)
{
	p->num_of_philos = ft_atoi(av[1]);
	p->time_to_die = ft_atoi(av[2]);
	p->time_to_eat = ft_atoi(av[3]);
	p->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		p->num_of_meals = ft_atoi(av[5]);
	else
		p->num_of_meals = -1;
	p->dead = 0;
	return (1);
}
