/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:37:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/06/05 16:32:48 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		kill(-1, SIGQUIT);
	}
}

int	main(int ac, char **av)
{
	t_philos		p;
	t_single_philo *philos;
	pid_t			*pids;

	signal(SIGINT, sig_handle);
	if (!check_args(av, ac))
		return (1);
	get_info(&p, ac, av);
	pids = malloc(sizeof(pid_t) * p.num_of_philos);
	if (!pids)
		return (1);
	philos = malloc(sizeof(t_single_philo) * p.num_of_philos);
	if (!philos)
	{
		free(pids);
		return (1);
	}
	init_philos(&p, philos, pids);
	unlink_semaphores(philos);
}
