#include "philo.h"

int free_staff(t_th *sing)
{
	int	i;

	i = 0;
	while (i < sing->game_link->number_of_philosophers)
	{
		pthread_mutex_destroy(&sing->game_link->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&sing->game_link->lock);
	free(sing->game_link->forks);
	free(sing);
	return (0);
}