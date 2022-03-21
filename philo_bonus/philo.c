/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:32:44 by ttokesi           #+#    #+#             */
/*   Updated: 2022/03/21 15:52:57 by ttokesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	chekker(int argc, char **strn, t_pg *game, int i)
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

static int	game_starter(t_pg *game)
{
	struct timeval	c_time;

	gettimeofday(&c_time, NULL);
	game->startime = (c_time.tv_usec / 1000) + (c_time.tv_sec * 1000);
	game->number_of_times_each_philosopher_must_eat = -1;
	game->pici = -2;
	game->death_status = 0;
	game->allphilo = 0;
	game->for_timer = 268;
	game->stopcount = 0;
	game->number_of_philosophers = 0;
	game->time_to_die = 0;
	game->time_to_eat = 0;
	game->time_to_sleep = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	int		check;
	t_pg	*game;

	if (argc == 5 || argc == 6)
	{	
		game = malloc(sizeof(t_pg));
		game_starter(game);
		check = chekker(argc, argv, game, 1);
		if (game->number_of_philosophers > 128)
			game->for_timer = 612;
		game->pici = game->number_of_times_each_philosopher_must_eat;
		if (check != 0)
			return (write(1, "Wrong input!\n", 13));
		load_game(game);
	}
	else
		return (write(1, "Wrong input!\n", 13));
	return (0);
}

//  system("leaks push_swap");
//   	fscanf(stdin, "c");
// getchar();