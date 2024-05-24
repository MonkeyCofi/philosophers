/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:47:17 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/24 16:18:41 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_philos *p, t_single_philo *philos)
{
	int	count;

	count = -1;
	while (++count < p->num_of_philos)
	{
		philos[count].pid = fork();
		if (philos[count].pid == -1)
			return (-1);
	}
	return (1);
}

int	get_info(t_philos *p, int ac, char **av)
{
	int	i;

	i = -1;
	p->num_of_philos = ft_atoi(av[1]);
	p->forks = sem_open("/forks", O_CREAT, 0644, p->num_of_philos);
	if (p->forks < 0)
		return (-1);
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
