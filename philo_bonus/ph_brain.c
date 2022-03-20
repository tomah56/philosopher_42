/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_brain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:32:05 by ttokesi           #+#    #+#             */
/*   Updated: 2022/03/20 03:00:42 by ttokesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	killer_the_ii(t_th	*sing, int stop, int time_to_die, int i)
{
	int				ch_eck;
	struct timeval	c_time;
	long			now;

	ch_eck = 0;
	while (i < stop)
	{
		gettimeofday(&c_time, NULL);
		now = (c_time.tv_usec / 1000) + (c_time.tv_sec * 1000)
			- sing[0].game_link->startime;
		if (now - sing[i].was_eat >= time_to_die)
		{
			sing[i].game_link->death_status = -3;
			printf("%ld %d died\n", now, sing[i].uniqid + 1);
			return (1);
		}
		if (sing[i].count_meal == sing[0].game_link->pici)
			ch_eck++;
		i++;
	}
	if (ch_eck == stop)
		return (1);
	return (0);
}

static void	*the_killer(void *arg)
{
	t_th	*sing;
	int		stop;
	int		time_to_die;

	sing = arg;
	stop = sing[0].game_link->number_of_philosophers;
	time_to_die = sing[0].game_link->time_to_die;
	while (1)
	{
		if (killer_the_ii(sing, stop, time_to_die, 0))
		{
			free_staff(sing);
			return (NULL);
		}
		usleep(512);
	}
	return (NULL);
}

static int	load_values(t_th *sing, t_pg *game)
{
	int	j;
	int	ret;

	j = 0;
	while (j < game->number_of_philosophers)
	{
		sing[j].game_link = game;
		sing[j].uniqid = j;
		sing[j].time_now = 0;
		sing[j].was_eat = 0;
		sing[j].count_meal = 0;
		sing[j].id = 0;
		j++;
	}

	return (0);
}

static int kill_them_all(t_th *sing)
{
	int j = 0;
	while (j < sing->game_link->number_of_philosophers)
	{
		// printf("pid id: %d\n", sing[j].id);
		kill(sing[j].id, 2);
		j++;
	}
	return (0);
}

int	load_game(t_pg *game)
{
	t_th	*sing;
	int		i;
	int		ret;

	sing = malloc((game->number_of_philosophers) * sizeof(t_th));
	if (sing == NULL)
		return (0);
	load_values(sing, game);
	sem_unlink("/spoons");
	sem_unlink("/print");
	game->spoons = sem_open("/spoons", O_CREAT | O_EXCL, S_IRWXU, game->number_of_philosophers);
	game->lock = sem_open("/print", O_CREAT | O_EXCL, S_IRWXU, 1);


	// sem_wait(game->spoons);
	// sem_post(game->spoons);
	i = 0;
	int j = 0;
	while (i < game->number_of_philosophers)
	{
		// j == i;
		// while (j != 0 && sing[j].id == 0)
		// {
		// 	j--;
		// }
		// if (i != 0 && sing[i - 1].id == 0 && sing[i].id == 0)
			sing[i].id = fork();
		if (sing[i].id == 0)
		{

			philo_run(&sing[i]);
			return (0);

		}
		// printf("id: %d     i: %d\n", sing[i].id, i);
		// return (0);
		// waitpid(sing[i].id, NULL, 0);
		i++;
	}
	i = 0;
	int rett = 0;
	while (i < game->number_of_philosophers)
	{

		// printf("id: %d  i: %d\n", sing[i].id, i);
		rett = waitpid(sing[i].id, NULL, 0);
		kill_them_all(sing);
		exit(EXIT_SUCCESS);
		// int j = 0;


		i++;
	}
	// if (rett)
	// {

	// 	while (j < game->number_of_philosophers)
	// 	{
	// 		kill(sing[j].id, 2);
	// 		j++;
	// 	}
	// }
	
	// game->allphilo = 1;

	return (0);
}

// sing[0].id = fork();
// if (sing[0].id == 0)
// {
// 	philo_run(&sing[0]);
// }
// sing[1].id = fork();
// if (sing[1].id == 0)
// {
// 	philo_run(&sing[1]);
// }