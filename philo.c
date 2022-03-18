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

static int	chekker(int argc ,char **strn, t_pg *game, int i)
{
	long	t;

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
		else if (i == 3 && (int)t < game->time_to_die)
			game->time_to_eat = (int)t;
		else if (i == 3 && (int)t >= game->time_to_die)
			game->time_to_eat = game->time_to_die + 1;
		else if (i == 4 && (int)t < game->time_to_die)
			game->time_to_sleep = (int)t;
		else if (i == 4 && (int)t >= game->time_to_die)
			game->time_to_sleep = game->time_to_die + 1;
		else if (i == 5)
			game->number_of_times_each_philosopher_must_eat = (int)t;
		i++;
	}
	return (0);
}

int	load_forks(t_pg *game)
{
	int	i;
	int	ret;

	game->forks = malloc(sizeof(pthread_mutex_t) * game->number_of_philosophers);
	if (game->forks == NULL)
		return (FAIL);
	i = 0;
	while (i < game->number_of_philosophers)
	{
		ret = pthread_mutex_init(&game->forks[i], NULL);
		if (ret != 0)
			return (FAIL);
		i++;
	}
	return (0);
}

int	game_starter(t_pg *game)
{
	struct timeval c_time;
	gettimeofday(&c_time, NULL);
	game->startime = (c_time.tv_usec / 1000) + (c_time.tv_sec * 1000); // c_time.tv_usec;
	game->number_of_times_each_philosopher_must_eat = -1;
	game->pici = -2;
	game->death_status = 0;
	game->allphilo = 0;
	game->for_timer = 128;
	game->stopcount = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	int		check;
	t_pg	game;

	if (argc == 5 || argc == 6)
	{
		game_starter(&game);
		check = chekker(argc, argv, &game, 1);
		if (game.number_of_philosophers > 128)
			game.for_timer = 512;
		if (game.number_of_philosophers == 1)
			return (write(1 ,"0 1 died\n", 9));
		game.pici = game.number_of_times_each_philosopher_must_eat;
		if (check != 0)
			return (write(1 ,"Wrong input!\n", 13));
		load_forks(&game);
		load_game(&game);
	}
	else
		return (write(1 ,"Wrong input!\n", 13));
	return (0);
}

//  system("leaks push_swap");
//   	fscanf(stdin, "c");
// getchar();