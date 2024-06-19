#include "philo.h"

void	*monitor(void *philo)
{
	t_philos		*info;
	t_single_philo	*p;
	int				i;
	int				phil_count;
	
	p = philo;
	info = p->info;
	phil_count = info->num_of_philos;
	while (1)
	{
		i = -1;
		while (++i < phil_count)
		{
			if (fully_devoured(p))
				break ;
			if (check_meal_time(&p[i]))
				break ;
		}
		if (i < phil_count)
			break ;
	}
	return (NULL);
}
