#include "philo.h"

static int	is_all_zero(const char *s)
{
	char	*ncon;
	int		i;
	int		j;

	ncon = (char *)s;
	i = 0;
	j = 0;
	while (ncon[i] != '\0')
		i++;
	while (ncon[j] == '0')
		j++;
	if (j == i)
		return (1);
	else
		return (0);
}

static int	chekker(int argc ,char **strn, t_th *game)
{
	long	t;
	int		i;

	i = 1;
	while (i < argc)
	{
		t = ft_long_atoi(strn[i]);
		if ((t == 0 && !is_all_zero(strn[i])) || t > INT_MAX
			|| ((i < 5 && t <= 0) || (i == 5 && t < 0)))
			return (1);
		if (i == 1)
			game->number_of_philosophers = (int)t;
		else if (i == 2)
			game->time_to_die = (int)t;
		else if (i == 3)
			game->time_to_eat = (int)t;
		else if (i == 4)
			game->time_to_sleep = (int)t;
		else if (i == 5)
			game->number_of_times_each_philosopher_must_eat = (int)t;
		i++;
	}
	return (0);
}

// static int what_is_hapening()
// {
	
// }

int	main(int argc, char **argv)
{
	int		check;
	t_th	*game;
	t_th	*sing;
	int 	i;
	int 	j;
	struct timeval c_time;
	long zero;

	gettimeofday( &c_time, NULL);
	// zero = c_time.tv_sec * 1000 + c_time.tv_usec / 1000;

	if (argc == 5 || argc == 6)
	{
		game = malloc(sizeof(t_pg));
		game->startime = c_time.tv_usec;
		game->number_of_times_each_philosopher_must_eat = 0;
		game->actual = 0;
		check = chekker(argc, argv, game);
		if (check != 0)
			return (write(1 ,"Wrong input!\n", 13));
		sing = malloc(game->number_of_philosophers * sizeof(t_th));
		j = 0;
		while (j < game->number_of_philosophers)
		{
			sing[j].game_link = game;
			sing[j].uniqid = j;
			j++;
		}
		pthread_mutex_init(&game->lock, NULL);
		i = 0;
		while (i < game->number_of_philosophers)
		{
			pthread_create(&sing[i].philo_thr, NULL, philo_run, &sing[i]);
			i++;
		}
	}
	else
	{
		write(1 ,"Wrong input!\n", 13);
		return (0);
	}
	i = 0;
	while (i < game->number_of_philosophers)
	{
		pthread_join(sing[i].philo_thr, NULL); //later
		i++;
	}
}

//  system("leaks push_swap");
//   	fscanf(stdin, "c");
// getchar();