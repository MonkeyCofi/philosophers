/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:48:17 by pipolint          #+#    #+#             */
/*   Updated: 2024/05/10 18:16:04 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// need to fix issues with one philosopher

int	main(int ac, char **av)
{
	t_philos	p;

	if (ac < 4 || ac > 6)
	{
		printf("Incorrect number of arguments\n");
		return (1);
	}
	get_info(&p, ac, av);
	if (init_all(&p) == -1)
		return (1);
	if (!not_dead(&p))
		destroy_all(&p);
}
