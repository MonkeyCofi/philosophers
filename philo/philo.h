/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:36:18 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/06 18:50:30 by pipolint         ###   ########.fr       */
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
	int				has_died;
	int				left_free;
	int				right_free;
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
	size_t			start_time;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	size_t			time_to_die;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	write_lock;
	t_single_philo	*philosophers;
}	t_philos;

/******************************/
/*------------Utils-----------*/
/******************************/

int		ft_atoi(char *str);
void	print_message(t_philos *ph, t_single_philo *p, char *str);
int		ft_usleep(size_t milliseconds);
int		ft_strcmp(char *str1, char *str2);
size_t	get_time_ms(void);

int		init_philo(t_philos *ph, t_single_philo *p, int i);
void	*monitor(void *philos);

/******************************/
/*----------Routines----------*/
/******************************/

void	philo_devour(t_single_philo *p);
void	philo_eepy(t_single_philo *p);

#endif
