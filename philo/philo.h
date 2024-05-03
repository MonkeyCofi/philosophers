/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:36:18 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/03 17:59:40 by pipolint         ###   ########.fr       */
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
	pthread_t	tid;
	int			phil_id;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		start_time;
	int			num_of_meals;
}	t_single_philo;

typedef struct s_philos
{
	int				num_of_philos;
	t_single_philo	*philosophers;
}	t_philos;

int	ft_atoi(char *str);

int		init_philo(t_single_philo *p, int i, int ac, char **av);
size_t	get_time_ms(void);

#endif