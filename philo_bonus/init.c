/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:47:17 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/10 00:41:58 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_single_philo(t_philos *info, t_single_philo *philo, int curr_philo)
{
	philo->phil_id = curr_philo + 1;
	philo->info = info;
	philo->has_left = 0;
	philo->has_right = 0;
	philo->meals_eaten = 0;
	philo->is_dead = &info->dead;
	philo->writing = info->writing;
	philo->eating = info->eating;
	philo->dead = info->dead_sem;
	philo->last_meal = get_time_ms();
	return (1);
}

static int	set_semaphores(t_philos *p)
{
	unlink_at_start();
	p->forks = sem_open("/forks", O_CREAT, 0644, p->num_of_philos);
	if (p->forks == SEM_FAILED)
	{
		write(2, "Unable to create forks semaphore\n", 33);
		return (-1);
	}
	p->dead_sem = sem_open("/dead_sem", O_CREAT, 0644, 1);
	if (p->dead_sem == SEM_FAILED)
	{
		write(2, "Unable to create dead semaphore\n", 32);
		return (-1);
	}
	p->writing = sem_open("/writing", O_CREAT, 0644, 1);
	if (p->writing == SEM_FAILED)
	{
		write(2, "Unable to create writing semaphore\n", 35);
		return (-1);
	}
	p->eating = sem_open("/eating", O_CREAT, 0644, 1);
	if (p->eating == SEM_FAILED)
	{
		write(2, "Unable to create eating semaphore\n", 34);
		return (-1);
	}
	p->test_sem = sem_open("/sem_thread", O_CREAT, 0644, 0);
	if (p->eating == SEM_FAILED)
	{
		write(2, "Unable to create thread semaphore\n", 34);
		return (-1);
	}
	return (1);
}

int	init_philos(t_philos *p, t_single_philo *philos, pid_t *pids)
{
	int		count;
	pthread_t	thread;

	count = -1;
	if (set_semaphores(p) == -1)
		return (-1);
	while (++count < p->num_of_philos)
	{
		init_single_philo(p, &philos[count], count);
		philos[count].pid = fork();
		if (philos[count].pid == 0)
			philo_routine(&philos[count]);
		else
			pids[count] = philos[count].pid;
	}
	if (pthread_create(&thread, NULL, monitor, philos) == -1)
		return (-1);
	if (pthread_join(thread, NULL) == -1)
		return (-1);
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
	p->start_time = get_time_ms();
	p->all_eaten = 0;
	return (1);
}
