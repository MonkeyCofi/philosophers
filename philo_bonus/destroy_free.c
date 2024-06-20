/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:16:48 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/14 16:01:01 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sem_error(char *failed_sem, char creat_delet)
{
	if (creat_delet == 'C')
	{
		write(2, "Unable to create ", 17);
		write(2, failed_sem, ft_strlen(failed_sem));
		write(2, " semaphore\n", 11);
	}
	else if (creat_delet == 'D')
	{
		write(2, "Unable to unlink ", 17);
		write(2, failed_sem, ft_strlen(failed_sem));
		write(2, " semaphore\n", 11);
	}
	return (-1);
}

int	unlink_semaphores(int start)
{
	int	ret;

	ret = 1;
	if (sem_unlink("/sem_forks") == -1 && !start)
		ret = sem_error("forks", 'D');
	if (sem_unlink("/sem_dead") == -1 && !start)
		ret = sem_error("dead", 'D');
	if (sem_unlink("/sem_writing") == -1 && !start)
		ret = sem_error("writing", 'D');
	if (sem_unlink("/sem_eating") == -1 && !start)
		ret = sem_error("eating", 'D');
	if (sem_unlink("/sem_monitor") == -1 && !start)
		ret = sem_error("monitor", 'D');
	if (sem_unlink("/sem_ended") == -1 && !start)
		ret = sem_error("ended", 'D');
	if (sem_unlink("/sem_routine") == -1 && !start)
		ret = sem_error("routine", 'D');
	if (sem_unlink("/sem_break") == -1 && !start)
		ret = sem_error("break", 'D');
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

void	close_sems(t_philos *info, t_single_philo *p)
{
	sem_close(p->dead);
	sem_close(p->eating);
	sem_close(p->writing);
	sem_close(info->forks);
	sem_close(info->routine_lock);
	sem_close(info->ended);
	sem_close(info->monitor_sem);
	sem_close(info->break_routine);
}
