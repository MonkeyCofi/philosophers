/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:16:48 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/05 17:11:27 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	unlink_semaphores(t_single_philo *philo)
{
	int	ret;

	ret = 1;
	if (sem_unlink("/forks") == -1)
	{
		//printf("Failed to unlink forks\n");
		perror("Forks");
		ret = -1;
	}
	if (sem_unlink("/dead_sem") == -1)
	{
		//printf("Failed to unlink dead sem\n");
		perror("Dead");
		ret = -1;
	}
	if (sem_unlink("/writing") == -1)
	{
		//printf("Failed to unlink writing sem\n");
		perror("Writing");
		ret = -1;
	}
	if (sem_unlink("/eating") == -1)
	{
		//printf("Failed to unlink eating sem\n");
		perror("Eating");
		ret = -1;
	}
	(void)philo;
	return (ret);
}
