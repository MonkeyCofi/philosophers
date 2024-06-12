/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:16:48 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/12 21:26:15 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlink_at_start()
{
	if (sem_open("/sem_forks", O_EXCL) != SEM_FAILED)
		sem_unlink("/sem_forks");
	if (sem_open("/sem_dead",  O_EXCL) != SEM_FAILED)
		sem_unlink("/sem_dead");
	if (sem_open("/sem_writing", O_EXCL) != SEM_FAILED)
		sem_unlink("/sem_writing");
	if (sem_open("/sem_eating", O_EXCL) != SEM_FAILED)
		sem_unlink("/sem_eating");
	if (sem_open("/sem_monitor", O_EXCL) != SEM_FAILED)
		sem_unlink("/sem_monitor");
	if (sem_open("/sem_ended", O_EXCL) != SEM_FAILED)
		sem_unlink("/sem_ended");
	if (sem_open("/sem_routine", O_EXCL) != SEM_FAILED)
		sem_unlink("/sem_routine");
}

int	unlink_semaphores()
{
	int	ret;

	ret = 1;
	if (sem_unlink("/sem_forks") == -1)
		ret = write(2, "Unable to unlink forks sem\n", 27);
	if (sem_unlink("/sem_dead") == -1)
		ret = write(2, "Unable to unlink dead sem\n", 26);
	if (sem_unlink("/sem_writing") == -1)
		ret = write(2, "Unable to unlink writing sem\n", 29);
	if (sem_unlink("/sem_eating") == -1)
		ret = write(2, "Unable to unlink eating sem\n", 28);
	if (sem_unlink("/sem_monitor") == -1)
		ret = write(2, "Unable to unlink thread sem\n", 28);
	if (sem_unlink("/sem_ended") == -1)
		ret = write(2, "Unable to unlink ended semaphore\n", 33);
	if (sem_unlink("/sem_routine") == -1)
		ret = write(2, "Unable to unlink routine sem\n", 29);
	if (ret > 1 || ret == -1)
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
	{
		waitpid(pids[i], &status, 0);	
	}
	return (WEXITSTATUS(status));
}

void	close_sems(t_single_philo *p)
{
	sem_close(p->dead);
	sem_close(p->eating);
	sem_close(p->writing);
}
