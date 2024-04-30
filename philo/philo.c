/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:48:17 by pipolint          #+#    #+#             */
/*   Updated: 2024/04/30 21:18:58 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*void_func(void *ptr)
{
	(void)ptr;
	return (NULL);
}

void	create_philos(t_philo *p)
{
	int	i;

	i = -1;
	p->ids = malloc(sizeof(pthread_t) * p->philo_num);
	while (++i < p->philo_num)
	{
		if (!pthread_create(&p->ids[i], NULL, void_func, (void *)p))
			printf("Thread creation successful\n");
		else
		{
			printf("Thread creation failedf\n");
			return ;
		}
	}
}

// ./philo [no of philosophers] [time to die] [time to eat] [time to sleep] [number of times each philo must eat(optional)]
int main(int ac, char **av)
{
	t_philo	p;

	if (ac > 6 || ac < 4)
	{
		printf("Incorrect number of arguments\n");
		return (1);
	}
	p.philo_num = ft_atoi(av[1]);
	create_philos(&p);
	(void)ac;
	(void)av;
}