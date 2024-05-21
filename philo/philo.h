/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:36:18 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/21 15:03:27 by pipolint         ###   ########.fr       */
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
	t_single_philo	*philosophers;
}	t_philos;

/******************************/
/*------------Utils-----------*/
/******************************/

int		ft_atoi(char *str);
int		ft_usleep(size_t milliseconds);
void	print_message(t_philos *ph, t_single_philo *p, char *str);
size_t	get_time_ms(void);
void	check_meal_time(t_philos *p, int i);

int		init_philo(t_philos *ph, t_single_philo *p, int i);
int		fully_devoured(t_single_philo *p);

/******************************/
/*------------Forks-----------*/
/******************************/

int		pick_left_fork(t_single_philo *ph);
int		pick_right_fork(t_single_philo *ph);
int		drop_left_fork(t_single_philo *p);
int		drop_right_fork(t_single_philo *p);
int		left_fork_free(t_single_philo *ph);
int		right_fork_free(t_single_philo *ph);
int		pick_up_forks(t_single_philo *p);
int		drop_forks(t_single_philo *p);
int	pick_forks(t_single_philo *p);

/******************************/
/*----------Routines----------*/
/******************************/

void	philo_hungy(t_single_philo *p);
void	philo_eepy(t_single_philo *p);
void	*philo_routine(void *ptr);

/******************************/
/*-----------Monitor----------*/
/******************************/

void	*monitor(void *philos);
int		not_dead(t_philos *p);

/******************************************/
/*------------Init and Destroy------------*/
/******************************************/

int		init_all(t_philos *p);
int		destroy_all(t_philos *p);
int		get_info(t_philos *p, int ac, char **av);

#endif
