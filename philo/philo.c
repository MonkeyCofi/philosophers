/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:48:17 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/22 16:38:59 by pipolint         ###   ########.fr       */
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
	int			init_status;

	if (ac < 5 || ac > 6)
	{
		write(2, "Incorrect number of arguments\n", 31);
		return (1);
	}
	get_info(&p, ac, av);
	init_status = init_all(&p);
	if (init_status == -1)
		return (1);
	destroy_all(&p);
}
