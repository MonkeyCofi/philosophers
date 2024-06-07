/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:35:47 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/07 17:45:29 by pipolint         ###   ########.fr       */
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
	pthread_t		tid;
	int				phil_id;
	int				meals_eaten;
	int				*is_dead;
	sem_t			*writing;
	sem_t			*eating;
	int				has_left;
	int				has_right;
	size_t			last_meal;
	void			*info;
}	t_single_philo;

typedef struct s_philos
{
	int				num_of_philos;
	int				dead;
	int				num_of_meals;
	int				all_eaten;
	sem_t			*forks;
	sem_t			*eating;
	sem_t			*dead_sem;
	sem_t			*writing;
	size_t			start_time;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	size_t			time_to_die;
	pthread_t		monitor;
}	t_philos;

/******************************/
/*------------Init------------*/
/******************************/

int		init_philos(t_philos *p, t_single_philo *philos, pid_t *pids);
int		get_info(t_philos *p, int ac, char **av);

/******************************/
/*------------Utils-----------*/
/******************************/

int		ft_atoi(char *str);
int		ft_usleep(size_t milliseconds);
size_t	get_time_ms(void);
void	print_message(t_philos *ph, t_single_philo *p, char *str);

/******************************/
/*-----------Routines---------*/
/******************************/

int		philo_routine(t_single_philo *philo);
int		eating(t_single_philo *philo);
int		sleeping(t_single_philo *philo);
int		thinking(t_single_philo *philo);

/******************************/
/*------------Checks----------*/
/******************************/

int		not_dead(t_philos *p);
int		check_meal_time(t_single_philo *philo);
int		all_meals_eaten(t_single_philo *philo);
void	*monitoring(void *philo);

/******************************/
/*-----------–Forks-----------*/
/******************************/

int		take_forks(t_single_philo *philo);
int		drop_left_fork(t_single_philo *philo);
int		drop_right_fork(t_single_philo *philo);

/******************************/
/*-----Frees and Destroys-----*/
/******************************/

int		kill_philos(t_philos *p, pid_t *pids);
int		unlink_semaphores(t_single_philo *philo);

#endif