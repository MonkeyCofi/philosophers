/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:16:48 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/09 23:04:06 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlink_at_start()
{
	if (sem_open("/forks", O_EXCL) != SEM_FAILED)
		sem_unlink("/forks");
	if (sem_open("/dead_sem",  O_EXCL) != SEM_FAILED)
		sem_unlink("/dead_sem");
	if (sem_open("/writing", O_EXCL) != SEM_FAILED)
		sem_unlink("/writing");
	if (sem_open("/eating", O_EXCL) != SEM_FAILED)
		sem_unlink("/eating");
	if (sem_open("/sem_thread", O_EXCL) != SEM_FAILED)
		sem_unlink("/sem_thread");
}

int	unlink_semaphores()
{
	int	ret;

	ret = 1;
	if (sem_unlink("/forks") == -1)
		ret = write(2, "Unable to unlink forks sem\n", 27);
	if (sem_unlink("/dead_sem") == -1)
		ret = write(2, "Unable to unlink dead sem\n", 26);
	if (sem_unlink("/writing") == -1)
		ret = write(2, "Unable to unlink writing sem\n", 29);
	if (sem_unlink("/eating") == -1)
		ret = write(2, "Unable to unlink eating sem\n", 28);
	if (sem_unlink("/sem_thread") == -1)
		ret = write(2, "Unable to unlink thread sem\n", 28);
	if (ret > 1)
		return (-1);
	return (ret);
}

void	free_all(t_single_philo **p, pid_t **pids)
{
	if (*p)
		free(*p);
	if (*pids)
		free(*pids);
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
