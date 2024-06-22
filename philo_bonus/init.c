/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:47:17 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/14 16:24:10 by pipolint         ###   ########.fr       */
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
	philo->end = 0;
	philo->ended = info->ended;
	philo->routine_lock = info->routine_lock;
	philo->last_meal = get_time_ms();
	return (1);
}

static int	set_semaphores(t_philos *p)
{
	unlink_semaphores(1);
	p->forks = sem_open("/sem_forks", O_CREAT, 0644, p->num_of_philos);
	if (p->forks == SEM_FAILED)
		return (sem_error("forks", 'C'));
	p->dead_sem = sem_open("/sem_dead", O_CREAT, 0644, 1);
	if (p->dead_sem == SEM_FAILED)
		return (sem_error("dead", 'C'));
	p->writing = sem_open("/sem_writing", O_CREAT, 0644, 1);
	if (p->writing == SEM_FAILED)
		return (sem_error("writing", 'C'));
	p->eating = sem_open("/sem_eating", O_CREAT, 0644, 1);
	if (p->eating == SEM_FAILED)
		return (sem_error("eating", 'C'));
	p->monitor_sem = sem_open("/sem_monitor", O_CREAT, 0644, 1);
	if (p->eating == SEM_FAILED)
		return (sem_error("monitor", 'C'));
	p->routine_lock = sem_open("/sem_routine", O_CREAT, 0644, 1);
	if (p->routine_lock == SEM_FAILED)
		return (sem_error("routine", 'C'));
	p->break_routine = sem_open("/sem_break", O_CREAT, 0644, 0);
	if (p->break_routine == SEM_FAILED)
		return (sem_error("break", 'C'));
	p->ended = sem_open("/sem_ended", O_CREAT, 0644, 1);
	if (p->ended == SEM_FAILED)
		return (sem_error("ended", 'C'));
	return (1);
}

int	init_philos(t_philos *p, t_single_philo *philos, pid_t *pids)
{
	int			count;
	// pthread_t	monitor;
	// pthread_t	death_monitor;

	count = -1;
	if (set_semaphores(p) == -1)
		return (-1);
	while (++count < p->num_of_philos)
	{
		init_single_philo(p, &philos[count], count);
		pids[count] = fork();
		if (!pids[count])
			philo_routine(&philos[count], philos);
		else
			philos[count].pid = pids[count];
	}
	// if (pthread_create(&death_monitor, NULL, death, philos) == -1)
	// 	return (-1);
	// if (p->num_of_meals > 0)
	// {
	// 	if (pthread_create(&monitor, NULL, main_monitor, philos) == -1)
	// 		return (-1);
	// 	if (pthread_join(monitor, NULL) == -1)
	// 		return (-1);
	// }
	// if (pthread_join(death_monitor, NULL) == -1)
	// 	return (-1);
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
