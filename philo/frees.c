/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:43:27 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/24 17:58:23 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_all(t_philos *p)
{
	int		i;

	i = -1;
	if (pthread_mutex_destroy(&p->dead_mutex) == -1)
		return (-1);
	if (pthread_mutex_destroy(&p->eating_mutex) == -1)
		return (-1);
	if (pthread_mutex_destroy(&p->write_lock) == -1)
		return (-1);
	while (++i < p->num_of_philos)
	{
		if (pthread_mutex_destroy(&p->forks[i]) == -1)
			return (-1);
	}
	if (p->philosophers)
		free(p->philosophers);
	if (p->forks)
		free(p->forks);
	if (p->forks_status)
		free(p->forks_status);
	return (-1);
}

int	free_mallocs(t_philos *p, int premature)
{
	if (p->philosophers)
		free(p->philosophers);
	if (p->forks)
		free(p->forks);
	if (p->forks_status)
		free(p->forks_status);
	if (premature)
		return (-1);
	return (0);
}
