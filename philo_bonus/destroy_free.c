/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:16:48 by pipolint          #+#    #+#             */
/*   Updated: 2024/07/06 16:14:11 by pipolint         ###   ########.fr       */
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
	if (sem_unlink("/sem_break") == -1 && !start)
		ret = sem_error("break", 'D');
	if (sem_unlink("/sem_check") == -1 && !start)
		ret = sem_error("check", 'D');
	if (sem_unlink("/sem_meals") == -1 && !start)
		ret = sem_error("meals", 'D');
	return (ret);
}

void	free_all(t_single_philo **p, pid_t **pids, int join)
{
	close_sems((*p)->info, (*p), 1);
	if (join)
	{
		pthread_join((*p)->monitor, NULL);
		pthread_join(((t_philos *)(*p)->info)->incrementor, NULL);
	}
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

void	close_sems(t_philos *info, t_single_philo *p, int close_writing)
{
	sem_close(p->dead);
	sem_close(p->eating);
	if (close_writing)
		sem_close(p->writing);
	sem_close(info->forks);
	sem_close(info->monitor_break);
	sem_close(info->break_check);
	sem_close(info->meals);
}
