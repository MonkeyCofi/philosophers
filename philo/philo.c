/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:48:17 by pipolint          #+#    #+#             */
/*   Updated: 2024/04/30 21:48:17 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*void_func(void *ptr)
{
	(void)ptr;
	return (NULL);
}

void	create_philos(t_test *t, t_philo *p)
{
	int	i;

	i = -1;
	p->ids = malloc(sizeof(pthread_t) * p->philo_num);
	while (++i < p->philo_num)
	{
		p->ids[i] = pthread_create(&p->ids[i], NULL, void_func, &p);
	}
}

void	init_struct(t_philo *p, int ac, char **av)
{
	p->philo_num = ft_atoi(av[1]);
	p->time_to_die = ft_atoi(av[2]);
	p->time_to_eat = ft_atoi(av[3]);
	p->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		p->num_of_meals = ft_atoi(av[5]);
}

// ./philo [no of philosophers] [time to die] [time to eat] [time to sleep] [number of times each philo must eat(optional)]
int main(int ac, char **av)
{
	t_philo	p;

	if (ac > 6 || ac < 4)
	{
		printf("Incorrect number of arguments\n");
		return (1);
	}
	init_struct(&p, ac, av);
	create_philos(&t, &p);
	(void)ac;
	(void)av;
}