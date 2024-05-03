/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:04:07 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/03 21:10:08 by pipolint         ###   ########.fr       */
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
	(void)milliseconds;
	return (1);
}

size_t	get_time_ms(void)
{
	struct timeval	t;
	int				milliseconds;

	if (gettimeofday(&t, NULL) == -1)
		return (-1);
	milliseconds = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (milliseconds);
}

void	print_message()
{
	
}