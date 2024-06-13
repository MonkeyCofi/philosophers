#include "philo.h"

void	*monitor(void *philo)
{
	t_philos		*info;
	t_single_philo	*p;
	int				i;
	int				breakout;
	
	p = philo;
	info = p->info;
	breakout = 0;
	while (1)
	{
		i = -1;
		while (++i < info->num_of_philos)
		{
			check_meal_time(&p[i]);
			if (fully_devoured(p) || !not_dead(info))
			{
				breakout = 1;
				break ;
			}
		}
		if (breakout)
			break ;
	}
	return (NULL);
}
