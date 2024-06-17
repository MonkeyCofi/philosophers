/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uwubuntu <uwubuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:36:18 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/17 12:34:03 by uwubuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_single_philo
{
	pthread_t		tid;
	int				phil_id;
	int				meals_eaten;
	int				*is_dead;
	int				*left_free;
	int				*right_free;
	size_t			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*eating_mutex;
	void			*info;
}	t_single_philo;

typedef struct s_philos
{
	int				num_of_philos;
	int				dead;
	int				num_of_meals;
	int				*forks_status;
	size_t			start_time;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	size_t			time_to_die;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	lock_order;
}	t_philos;

/******************************/
/*------------Utils-----------*/
/******************************/

int		ft_atoi(char *str);
int		ft_usleep(size_t milliseconds);
void	print_message(t_philos *ph, t_single_philo *p, char *str);
size_t	get_time_ms(void);

int		init_philo(t_philos *ph, t_single_philo *p, int i);

/******************************/
/*-----------Checks-----------*/
/******************************/

int		not_dead(t_philos *p);
void	set_dead(t_single_philo *philo);
int		check_meal_time(t_single_philo *p);
int		fully_devoured(t_single_philo *p);

/******************************/
/*------------Forks-----------*/
/******************************/

int		pick_left_fork(t_single_philo *ph);
int		pick_right_fork(t_single_philo *ph);
int		left_fork_free(t_single_philo *ph);
int		right_fork_free(t_single_philo *ph);
int		drop_forks(t_single_philo *p);
int		pick_forks(t_single_philo *p);
int		drop_left_fork(t_single_philo *p);
int		drop_right_fork(t_single_philo *p);

/******************************/
/*----------Routines----------*/
/******************************/

int		eating_preparation(t_single_philo *p);
void	sleeping(t_single_philo *p);
void	*philo_routine(void *ptr);
void	thinking(t_single_philo *p);
int		eating(t_single_philo *p);
int		fully_devoured(t_single_philo *p);

/******************************/
/*-----------Monitor----------*/
/******************************/

void	*monitor(void *philos);

/******************************************/
/*------------Init and Destroy------------*/
/******************************************/

int		init_all(t_philos *p, t_single_philo *philos);
int		destroy_all(t_philos *p, t_single_philo **philos);


int		get_info(t_philos *p, int ac, char **av);
int		free_mallocs(t_philos *p, t_single_philo **philos, int premature);

#endif
