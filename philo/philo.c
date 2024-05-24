/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:48:17 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/24 10:42:59 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *philos)
{
	t_philos	*p;
	int			i;

	i = 0;
	p = (t_philos *)philos;
	while (not_dead(p))
	{
		if (i == p->num_of_philos)
			i = 0;
		check_meal_time(p, i);
		if (fully_devoured(&p->philosophers[i]))
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

int	main(int ac, char **av)
{
	t_philos	p;
	int			init_status;
	int			valid;

	valid = is_valid(av);
	if (!valid)
	{
		write(2, "Arguments can only be numbers\n", 31);
		return (1);
	}
	else if (valid == -1)
	{
		write(2, "Arguments cannot be negative numbers\n", 38);
		return (1);
	}
	if (ac < 5 || ac > 6)
	{
		write(2, "Incorrect number of arguments\n", 31);
		return (1);
	}
	get_info(&p, ac, av);
	init_status = init_all(&p);
	if (init_status == -1)
		return (1);
	destroy_all(&p);
}
