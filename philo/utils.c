/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:04:07 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/07 14:47:21 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	res;
	int	neg;

	res = 0;
	neg = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + ((*str) - '0');
		str++;
	}
	return (res * neg);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	s;

	s = get_time_ms();
	while (get_time_ms() - s < milliseconds)
		usleep(500);
	return (1);
}

size_t	get_time_ms(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		return (-1);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	print_message(t_philos *ph, t_single_philo *p, char *str)
{
	if (not_dead(ph))
	{
		pthread_mutex_lock(&ph->write_lock);
		printf("%ld %d %s\n", get_time_ms() - ph->start_time, p->phil_id, str);
		pthread_mutex_unlock(&ph->write_lock);
	}
}

int	not_dead(t_philos *p)
{
	if (pthread_mutex_lock(&p->read_mutex) == -1)
		return (-1);
	if (!p->dead)
	{
		if (pthread_mutex_unlock(&p->read_mutex) == -1)
			return (-1);
		return (1);
	}
	if (pthread_mutex_unlock(&p->read_mutex) == -1)
		return (-1);
	return (0);
}