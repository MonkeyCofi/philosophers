/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:48:17 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/21 18:06:05 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *philos)
{
	t_philos	*p;
	int			i;

	i = 0;
	p = (t_philos *)philos;
	while (not_dead(p))
	{
		if (i == p->num_of_philos)
			i = 0;
		check_meal_time(p, i);
		if (fully_devoured(&p->philosophers[i]))
			break ;
		i++;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philos	p;

	if (ac < 4 || ac > 6)
	{
		printf("Incorrect number of arguments\n");
		return (1);
	}
	get_info(&p, ac, av);
	if (init_all(&p) == -1)
		return (1);
	destroy_all(&p);
}
