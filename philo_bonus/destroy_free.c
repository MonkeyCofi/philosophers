/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:16:48 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/08 15:06:04 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	unlink_semaphores()
{
	int	ret;

	ret = 1;
	if (sem_unlink("/forks") == -1)
	{
		perror("Forks");
		ret = -1;
	}
	if (sem_unlink("/dead_sem") == -1)
	{
		perror("Dead");
		ret = -1;
	}
	if (sem_unlink("/writing") == -1)
	{
		perror("Writing");
		ret = -1;
	}
	if (sem_unlink("/eating") == -1)
	{
		perror("Eating");
		ret = -1;
	}
	if (sem_unlink("/sem_thread") == -1)
	{
		perror("Sem_test");
		ret = -1;
	}
	return (ret);
}

int	wait_philos(pid_t *pids, t_philos *info)
{
	int	i;
	int	status;

	i = -1;
	while (++i < info->num_of_philos)
		waitpid(pids[i], &status, 0);
	return (WEXITSTATUS(status));
}
