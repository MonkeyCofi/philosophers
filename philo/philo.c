/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:48:17 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/03 21:24:35 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *philos)
{
	int	i;
	t_philos	*p;
	
	i = -1;
	p = philos;
	while (++i < p->num_of_philos)
	{
		if (!*p->philosophers[i].is_dead)
		{
			pthread_mutex_lock(p->philosophers[i].eating_mutex);
			if (get_time_ms() > p->time_to_die)
				*p->philosophers[i].is_dead = 1;
			print_message(p, &p->philosophers[i], "has died");
			pthread_mutex_unlock(p->philosophers[i].eating_mutex);
		}
	}
	return (NULL);
}

void	*philo_routine(void *ptr)
{
	t_single_philo	*p;
	t_philos		*info;
	// pthread_t		monitor_thread;

	p = ptr;
	info = p->info;
	if (p->phil_id % 2)
		ft_usleep(100);
	while (!info->dead)
	{
		philo_devour(p);
		if (p->meals_eaten == info->num_of_meals)
			break ;
		philo_eepy(p);
		print_message(info, p, "is thinking");
	}
	// pthread_create(&monitor_thread, NULL, monitor, (void *)info);
	return (NULL);
}

int	create_philos(t_philos *p)
{
	int	i;
	pthread_t	monitor_thread;

	p->philosophers = malloc(sizeof(t_single_philo) * p->num_of_philos);
	if (!p->philosophers)
		return (-1);
	p->forks = malloc(sizeof(pthread_mutex_t) * p->num_of_philos);
	if (!p->forks)
		return (-1);
	p->start_time = get_time_ms();
	i = -1;
	while (++i < p->num_of_philos)
		pthread_mutex_init(&p->forks[i], NULL);
	pthread_mutex_init(&p->write_lock, NULL);
	pthread_mutex_init(&p->eating_mutex, NULL);
	i = -1;
	while (++i < p->num_of_philos)
	{
		if (init_philo(p, &p->philosophers[i], i) == -1)
			return (-1);
	}
	pthread_create(&monitor_thread, NULL, monitor, (void*)p);
	// i = -1;
	// while (++i < p->num_of_philos)
	// {
	// 	if (pthread_join(p->philosophers[i].tid, NULL) == -1)
	// 		return (-1);
	// }
	return (1);
}

int	init_philo(t_philos *ph, t_single_philo *p, int i)
{
	p->phil_id = i + 1;
	p->left_fork = &ph->forks[i];
	if (i == ph->num_of_philos - 1)
		p->right_fork = &ph->forks[i - ph->num_of_philos + 1];
	else
		p->right_fork = &ph->forks[i + 1];
	p->write_lock = &ph->write_lock;
	p->is_dead = &ph->dead;
	p->info = (void *)ph;
	p->right_free = 1;
	p->left_free = 1;
	p->meals_eaten = 0;
	p->last_meal = get_time_ms();
	p->eating_mutex = &ph->eating_mutex;
	if (pthread_create(&p->tid, NULL, philo_routine, (void *)p) == -1)
		return (-1);
	return (1);
}

// ./philo [no of philosophers] [time to die] [time to eat] [time to sleep] [number of times each philo must eat(optional)]
int	main(int ac, char **av)
{
	t_philos		p;

	if (ac < 4 || ac > 6)
	{
		printf("Incorrect number of arguments\n");
		return (1);
	}
	p.num_of_philos = ft_atoi(av[1]);
	p.time_to_die = ft_atoi(av[2]);
	p.time_to_eat = ft_atoi(av[3]);
	p.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		p.num_of_meals = ft_atoi(av[5]);
	else
		p.num_of_meals = -1;
	p.dead = 0;
	if (create_philos(&p) == -1)
		return (1);
	int i = -1;
	while (++i < p.num_of_philos)
	{
		if (pthread_join(p.philosophers[i].tid, NULL) == -1)
			return (-1);
	}
	i = -1;
	while (++i < p.num_of_philos)
		pthread_mutex_destroy(&p.forks[i]);
}
