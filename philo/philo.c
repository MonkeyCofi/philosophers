/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:48:17 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/03 18:03:20 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *ptr)
{
	t_single_philo	*p;

	p = ptr;
	(void)ptr;
	return (NULL);
}

int	create_philos(t_philos *philos, char **av, int ac)
{
	int	i;

	philos->philosophers = malloc(sizeof(t_single_philo) * philos->num_of_philos);
	if (!philos->philosophers)
		return (-1);
	i = -1;
	while (++i < philos->num_of_philos)
	{
		if (init_philo(&philos->philosophers[i], i, ac, av) == -1)
			return (-1);
		//if (pthread_join(philos->philosophers[i].tid, NULL) == -1)
		//	return (-2);
	}
	return (1);
}

int	init_philo(t_single_philo *p, int i, int ac, char **av)
{
	p->phil_id = i;
	p->time_to_die = ft_atoi(av[2]);
	p->time_to_eat = ft_atoi(av[3]);
	p->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		p->num_of_meals = ft_atoi(av[5]);
	else
		p->num_of_meals = -1;
	if (pthread_create(&p->tid, NULL, philo_routine, p) == -1)
		return (-1);
	return (1);
}

// ./philo [no of philosophers] [time to die] [time to eat] [time to sleep] [number of times each philo must eat(optional)]
int main(int ac, char **av)
{
	t_philos		p;

	if (ac < 4 || ac > 6)
	{
		printf("Incorrect number of arguments\n");
		return (1);
	}
	p.num_of_philos = ft_atoi(av[1]);
	if (create_philos(&p, av, ac) == -1)
		return (1);
}