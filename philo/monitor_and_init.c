/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_and_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:32:33 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/13 16:32:46 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *philos)
{
	t_philos	*p;
	int			i;
	
	i = 0;
	p = philos;
	while (not_dead(p))
	{
		if (i == p->num_of_philos)
			i = 0;
		// check_meal_time(p, i);
		pthread_mutex_lock(&p->eating_mutex);
		if (get_time_ms() > p->philosophers[i].last_meal + p->time_to_die)
		{
			*p->philosophers[i].is_dead = 1;
			pthread_mutex_lock(p->philosophers[i].write_lock);
			printf("%ld %d has died\n", get_time_ms() - p->start_time, p->philosophers[i].phil_id);
			pthread_mutex_unlock(p->philosophers[i].write_lock);
		}
		pthread_mutex_unlock(&p->eating_mutex);
		i++;
	}
	return (NULL);
}

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
	if (pthread_mutex_init(&p->write_lock, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&p->eating_mutex, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&p->dead_mutex, NULL) == -1)
		return (-1);
	return (1);
}

int	init_all(t_philos *p)
{
	int	i;

	p->philosophers = malloc(sizeof(t_single_philo) * p->num_of_philos);
	if (!p->philosophers)
		return (-1);
	if (init_mutexes(p) == -1)
		return (-1);
	p->start_time = get_time_ms();
	i = -1;
	while (++i < p->num_of_philos)
	{
		if (init_philo(p, &p->philosophers[i], i) == -1)
			return (-1);
	}
	while (++i < p->num_of_philos)
	{
		if (pthread_join(p->philosophers[i].tid, NULL) == -1)
			return (-1);
	}
	if (pthread_create(&p->monitor, NULL, monitor, (void*)p) == -1)
		return (-1);
	if (pthread_join(p->monitor, NULL) == -1)
		return (-1);
	return (1);
}

int	destroy_all(t_philos *p)
{
	int		i;

	i = -1;
	while (++i < p->num_of_philos)
	{
		if (pthread_mutex_destroy(&p->forks[i]) == -1)
			return (-1);
	}
	if (pthread_mutex_destroy(&p->write_lock) == -1)
		return (-1);
	if (pthread_mutex_destroy(&p->eating_mutex) == -1)
		return (-1);
	if (pthread_mutex_destroy(&p->dead_mutex) == -1)
		return (-1);
	//if (p->philosophers)
	//	free(p->philosophers);
	//if (p->forks)
	//	free(p->forks);
	return (1);
}

int	init_philo(t_philos *ph, t_single_philo *p, int i)
{
	p->phil_id = i + 1;
	p->left_fork = &ph->forks[i];
	if (ph->num_of_philos == 1)
	{
		p->right_fork = &ph->forks[i];
		p->left_fork = &ph->forks[i];
	}
	if (ph->num_of_philos > 1 && i == ph->num_of_philos - 1)
		p->right_fork = &ph->forks[i - ph->num_of_philos + 1];
	else if (ph->num_of_philos > 1 && i != ph->num_of_philos - 1)
		p->right_fork = &ph->forks[i + 1];
	p->write_lock = &ph->write_lock;
	if (not_dead(ph))
		p->is_dead = &ph->dead;
	p->eating_mutex = &ph->eating_mutex;
	p->info = (void *)ph;
	p->right_free = ph->num_of_philos > 1;
	p->left_free = 1;
	p->meals_eaten = 0;
	p->last_meal = get_time_ms();
	p->has_died = 0;
	if (pthread_create(&p->tid, NULL, philo_routine, (void *)p) == -1)
		return (-1);
	return (1);
}

void	get_info(t_philos *p, int ac, char **av)
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
}
