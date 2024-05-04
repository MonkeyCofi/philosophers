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
	(void)philos;
	return (NULL);
}

void	*philo_routine(void *ptr)
{
	t_single_philo	*p;
	t_philos		*info;

	p = ptr;
	info = p->info;
	// printf("Philos: %d\n", info->num_of_philos);
	// if (p->phil_id % 2)
	// 	printf("Odd Philosopher:\t%d\n", p->phil_id);
	// else
	// 	printf("Even Philosopher:\t%d\n", p->phil_id);
	while (!info->dead)
	{
		print_message(p);
	}
	return (NULL);
}

int	create_philos(t_philos *p)
{
	int	i;

	p->philosophers = malloc(sizeof(t_single_philo) * p->num_of_philos );
	if (!p->philosophers)
		return (-1);
	p->forks = malloc(sizeof(pthread_mutex_t) * p->num_of_philos );
	if (!p->forks)
		return (-1);
	i = -1;
	while (++i < p->num_of_philos)
		pthread_mutex_init(&p->forks[i], NULL);
	i = -1;
	while (++i < p->num_of_philos)
	{
		if (init_philo(p, &p->philosophers[i], i) == -1)
			return (-1);
	}
	i = -1;
	while (++i < p->num_of_philos)
	{
		if (pthread_join(p->philosophers[i].tid, NULL) == -1)
			return (-1);
	}
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
	if (create_philos(&p) == -1)
		return (1);
}
