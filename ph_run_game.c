#include "philo.h"

void *philo_run(void *arg)
{
	t_pg *game;
	// game = (t_pg *)arg;
	// static int	runcount;

	t_th *sing;

	sing = (t_th *)arg;
	struct timeval c_time;
	long zero;

	gettimeofday( &c_time, NULL);
	// game->startime = c_time.tv_usec;


	// t_th *infop;

	// infop = (t_th *)arg;
	game = sing->game_link;
	// write(1,"I Am Dancing\n", 13);
	pthread_mutex_lock(&game->lock);
	// if (game->actual == 0)
	crossroad("\nhello ", game->actual);
	crossroad("\nfromuniq ", sing->uniqid);
	game->actual++;
	// infop->uniqid = game->actual;
	pthread_mutex_unlock(&game->lock);
	// printf("hello %d\n", game->actual);

	usleep(1000);
	
	pthread_mutex_lock(&game->lock);
	zero = c_time.tv_usec - game->startime;
	crossroad("\nPhilo numbr: ", sing->uniqid);
	crossroad("\ntime: ", (int)zero);
	// crossroad("\nPhilo numbr: ", game->actual);
	pthread_mutex_unlock(&game->lock);

	return (NULL);
}