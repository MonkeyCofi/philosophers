/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:32:34 by pipolint          #+#    #+#             */
/*   Updated: 2024/07/01 20:01:04 by pipolint         ###   ########.fr       */
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

// int	ft_usleep(size_t milliseconds, t_single_philo *p)
int	ft_usleep(size_t milliseconds)
{
	size_t	s;

	s = get_time_ms();
	// while (get_time_ms() - s < milliseconds && !should_break(p))
	while (get_time_ms() - s < milliseconds)
	{
		usleep(250);
	}
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
	// if (not_dead(ph))
	if (!should_break(p))
	{
		sem_wait(p->writing);
		printf("%ld %d %s\n", get_time_ms() - ph->start_time, p->phil_id, str);
		sem_post(p->writing);
	}
}

size_t	ft_strlen(char *str)
{
	if (!str)
		return (0);
	if (!*str)
		return (0);
	return (ft_strlen(str + 1) + 1);
}
