/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:48:17 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/30 19:41:48 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *philo)
{
	t_philos	*p;
	int			i;

	i = 0;
	p = ((t_single_philo *)philo)->info;
	while (not_dead(p))
	{
		if (i == p->num_of_philos)
			i = 0;
		check_meal_time(philo);
		if (fully_devoured(philo))
			break ;
		i++;
	}
	return (NULL);
}

static int	only_digits(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			flag *= -1;
		i++;
	}
	while (str[++i] && flag)
	{
		if (str[i] >= '0' && str[i] <= '9')
			continue ;
		else
			flag = 0;
	}
	return (flag);
}

static int	is_valid(char **av)
{
	int	i;
	int	res;

	i = 1;
	while (av[i])
	{
		res = only_digits(av[i++]);
		if (!res)
			return (res);
	}
	return (res);
}

static int	check_args(char **av, int ac)
{
	int	valid;

	if (ac < 5 || ac > 6)
	{
		write(2, "Incorrect number of arguments\n", 31);
		return (0);
	}
	valid = is_valid(av);
	if (!valid)
	{
		write(2, "Arguments can only be numbers\n", 31);
		return (0);
	}
	else if (valid == -1)
	{
		write(2, "Arguments cannot be negative numbers\n", 38);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philos		p;
	t_single_philo	*philos;
	int				init_status;

	if (!check_args(av, ac))
		return (1);
	get_info(&p, ac, av);
	philos = malloc(sizeof(t_single_philo) * p.num_of_philos);
	if (!philos)
		return (1);
	init_status = init_all(&p, philos);
	if (init_status == -1)
		return (1);
	destroy_all(&p, &philos);
}
