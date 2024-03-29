/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_brain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:32:05 by ttokesi           #+#    #+#             */
/*   Updated: 2022/03/24 16:36:01 by ttokesi          ###   ########.fr       */
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
			return (NULL);
		usleep(516);
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
		j++;
	}
	ret = pthread_mutex_init(&game->lock, NULL);
	if (ret != 0)
		return (FAIL);
	return (0);
}

static int	norm_join(t_th	*sing, t_pg *game)
{
	int	i;
	int	ret;

	game->allphilo = 1;
	i = 0;
	while (i < game->number_of_philosophers)
	{
		ret = pthread_join(sing[i].philo_thr, NULL);
		if (ret != 0)
			return (free_staff(sing));
		i++;
	}
	ret = pthread_join(game->watch_dog, NULL);
	if (ret != 0)
		return (free_staff(sing));
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
	i = 0;
	while (i < game->number_of_philosophers)
	{
		ret = pthread_create(&sing[i].philo_thr, NULL, philo_run, &sing[i]);
		if (ret != 0)
			return (free_staff(sing));
		i++;
	}
	ret = pthread_create(&game->watch_dog, NULL, &the_killer, sing);
	if (ret != 0)
		return (free_staff(sing));
	norm_join(sing, game);
	free_staff(sing);
	return (0);
}
