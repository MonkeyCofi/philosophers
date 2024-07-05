/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:35:47 by pipolint          #+#    #+#             */
/*   Updated: 2024/07/05 12:04:49 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <string.h>

typedef struct s_single_philo
{
	pid_t			pid;
	int				phil_id;
	int				meals_eaten;
	int				*is_dead;
	int				has_left;
	int				has_right;
	int				*end;
	void			*info;
	size_t			last_meal;
	sem_t			*writing;
	sem_t			*eating;
	sem_t			*dead;
	sem_t			*ended;
	sem_t			*routine_lock;
	sem_t			*send_kill;
	pthread_t		monitor;
}	t_single_philo;

typedef struct s_philos
{
	int				num_of_philos;
	int				dead;
	int				num_of_meals;
	int				all_eaten;
	int				end;
	pid_t			*pids;
	sem_t			*forks;
	sem_t			*eating;
	sem_t			*dead_sem;
	sem_t			*writing;
	sem_t			*send_kill;
	sem_t			*freeing;
	sem_t			*monitor_break;
	sem_t		 	*break_check;
	sem_t			*meals;
	sem_t			*picking;
	size_t			start_time;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	size_t			time_to_die;
	pthread_t		freeing_thread;
	pthread_t		incrementor;
}	t_philos;

/******************************/
/*------------Init------------*/
/******************************/

int		init_philos(t_philos *p, t_single_philo *philos, pid_t *pids);
int		get_info(t_philos *p, int ac, char **av);
int		sem_error(char *failed_sem, char creat_delet);

/******************************/
/*------------Utils-----------*/
/******************************/

int		ft_atoi(char *str);
size_t	ft_strlen(char *str);
int		ft_usleep(size_t milliseconds, t_single_philo *p);
size_t	get_time_ms(void);
void	print_message(t_philos *ph, t_single_philo *p, char *str);

/******************************/
/*-----------Routines---------*/
/******************************/

int		philo_routine(t_single_philo *philo, t_single_philo *philo_array);
int		eating(t_single_philo *philo);
int		sleeping(t_single_philo *philo);
int		thinking(t_single_philo *philo);

/******************************/
/*------------Checks----------*/
/******************************/

int		not_dead(t_philos *p);
int		check_meal_time(t_single_philo *philo);
int		all_meals_eaten(t_single_philo *philo);
void	set_dead(t_single_philo *philo);
int		eaten_fully(t_philos *info);

/******************************/
/*-----------–Forks-----------*/
/******************************/

int		take_forks(t_single_philo *philo);
int		drop_left_fork(t_single_philo *philo);
int		drop_right_fork(t_single_philo *philo);

/******************************/
/*-----Frees and Destroys-----*/
/******************************/

int		unlink_semaphores(int start);
void	close_sems(t_philos *info, t_single_philo *p, int close_writing);
int		wait_philos(pid_t *pids, t_philos *info);
void	free_all(t_single_philo **p, pid_t **pids);

/******************************/
/*-----------Threads----------*/
/******************************/

void	*philo_monitor(void *philo);
int		should_break(t_single_philo *p);
void	*free_resources(void *philo);
void	*increment(void *philo);

#endif