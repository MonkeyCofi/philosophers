/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:48:17 by pipolint          #+#    #+#             */
/*   Updated: 2024/04/30 18:40:02 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define LIMIT 500

void	*print_test(void *str)
{
	printf("%s\n", (char *)str);
	return (NULL);
}

// ./philo [no of philosophers] [time to die] [time to eat] [time to sleep] [number of times each philo must eat(optional)]
int main(int ac, char **av)
{
	// create 500 threads
	pthread_t	id;

	for (int i = 0; i < LIMIT; i++)
	{
		if (!pthread_create(&id, NULL, print_test, (void *)"In thread"))
			printf("Thread %ld creation successful\n", id);
		else
			printf("Failed to create thread\n");
	}
	(void)ac;
	(void)av;
}