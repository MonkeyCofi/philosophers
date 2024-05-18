/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:48:17 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/10 18:16:04 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	drop_left_fork(t_single_philo *p)
{
	// t_philos	*ph;

	// ph = p->info;
	pthread_mutex_lock(p->left_fork);
	if (!p->left_free)
	{
		// print_message(ph, p, "has dropped their right fork");
		p->left_free = 1;
	}
	pthread_mutex_unlock(p->left_fork);
	return (1);
}

int	drop_right_fork(t_single_philo *p)
{
	// t_philos	*ph;

	// ph = p->info;
	pthread_mutex_lock(p->right_fork);
	if (!p->right_free)
	{
		// print_message(ph, p, "has dropped their right fork");
		p->right_free = 1;
	}
	pthread_mutex_unlock(p->right_fork);
	return (1);
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
	if (!not_dead(&p))
		destroy_all(&p);
}
