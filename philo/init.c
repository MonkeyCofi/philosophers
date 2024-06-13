/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:32:33 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/13 20:58:31 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_philos *p)
{
	int	i;

	p->forks = malloc(sizeof(pthread_mutex_t) * p->num_of_philos);
	if (!p->forks)
		return (-1);
	i = -1;
	while (++i < p->num_of_philos)
	{
		if (pthread_mutex_init(&p->forks[i], NULL) == -1)
			return (-1);
	}
	if (pthread_mutex_init(&p->dead_mutex, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&p->write_lock, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&p->eating_mutex, NULL) == -1)
		return (-1);
	return (1);
}

int	create_threads(t_philos *p, t_single_philo *ph)
{
	int	i;

	i = -1;
	while (++i < p->num_of_philos)
	{
		if (init_philo(p, &ph[i], i) == -1)
			return (destroy_all(p, &ph));
		if (pthread_create(&ph[i].tid, NULL, philo_routine, &ph[i]) == -1)
			return (destroy_all(p, &ph));
	}
	if (pthread_create(&p->monitor, NULL, monitor, (void *)ph) == -1)
		return (destroy_all(p, &ph));
	return (1);
}

int	init_all(t_philos *p, t_single_philo *philos)
{
	int	i;

	if (init_mutexes(p) == -1)
		return (free_mallocs(p, &philos, 1));
	p->start_time = get_time_ms();
	if (create_threads(p, philos) == -1)
		return (-1);
	i = -1;
	while (++i < p->num_of_philos)
	{
		if (pthread_join(philos[i].tid, NULL) == -1)
			return (destroy_all(p, &philos));
	}
	if (pthread_join(p->monitor, NULL) == -1)
		return (destroy_all(p, &philos));
	return (1);
}

int	init_philo(t_philos *ph, t_single_philo *p, int i)
{
	p->phil_id = i + 1;
	p->left_fork = &ph->forks[i];
	p->right_fork = &ph->forks[(i + 1) % ph->num_of_philos];
	p->write_lock = &ph->write_lock;
	p->is_dead = &ph->dead;
	p->eating_mutex = &ph->eating_mutex;
	p->info = (void *)ph;
	p->left_free = &ph->forks_status[i];
	p->right_free = &ph->forks_status[(i + 1) % ph->num_of_philos];
	p->meals_eaten = 0;
	p->last_meal = get_time_ms();
	p->dead_mutex = &ph->dead_mutex;
	return (1);
}

int	get_info(t_philos *p, int ac, char **av)
{
	int	i;

	i = -1;
	p->num_of_philos = ft_atoi(av[1]);
	p->forks_status = malloc(sizeof(int) * p->num_of_philos);
	if (!p->forks_status)
		return (-1);
	while (++i < p->num_of_philos)
		p->forks_status[i] = 1;
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
