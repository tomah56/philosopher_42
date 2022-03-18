/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:32:34 by ttokesi           #+#    #+#             */
/*   Updated: 2022/03/18 14:07:01 by ttokesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	status_print(t_pg *game, t_th *sing, int s_witch)
{
	char			*temp;
	struct timeval	c_time;

	if (s_witch == SLEEP)
		temp = "is sleeping";
	else if (s_witch == EAT)
		temp = "is eating";
	else if (s_witch == THINK)
		temp = "is thinking";
	else if (s_witch == TFORK)
		temp = "has taken a fork";
	pthread_mutex_lock(&game->lock);
	gettimeofday(&c_time, NULL);
	sing->time_now = ((c_time.tv_usec / 1000) + (c_time.tv_sec * 1000))
		- game->startime;
	if (game->death_status == 0)
		printf("%ld %d %s\n", sing->time_now, sing->uniqid + 1, temp);
	pthread_mutex_unlock(&game->lock);
}

static void	u_my_sleep(long time_to, int for_time)
{
	struct timeval	c_time;
	long			start;
	long			i;

	i = 0;
	gettimeofday(&c_time, NULL);
	start = (c_time.tv_usec / 1000) + (c_time.tv_sec * 1000);
	while (i < start + time_to)
	{
		usleep(for_time);
		gettimeofday(&c_time, NULL);
		i = (c_time.tv_usec / 1000) + (c_time.tv_sec * 1000);
	}
}

static void	feeding_sycle(t_pg *game, t_th *sing)
{
	status_print(game, sing, EAT);
	sing->was_eat = sing->time_now;
	sing->count_meal++;
	u_my_sleep(game->time_to_eat, game->for_timer);
	if (sing->uniqid != game->number_of_philosophers - 1)
		pthread_mutex_unlock(&game->forks[sing->uniqid + 1]);
	else
		pthread_mutex_unlock(&game->forks[0]);
	pthread_mutex_unlock(&game->forks[sing->uniqid]);
	if (sing->count_meal == sing->game_link->pici)
		return ;
	status_print(game, sing, SLEEP);
	u_my_sleep(game->time_to_sleep, game->for_timer);
	status_print(game, sing, THINK);
}

static void	eat_think_sleep(t_pg *game, t_th *sing)
{
	if (sing->uniqid != game->number_of_philosophers - 1)
		pthread_mutex_lock(&game->forks[sing->uniqid + 1]);
	else if (game->number_of_philosophers != 1)
	{
		pthread_mutex_lock(&game->forks[0]);
	}
	status_print(game, sing, TFORK);
	if (game->number_of_philosophers != 1)
		pthread_mutex_lock(&game->forks[sing->uniqid]);
	else
	{
		u_my_sleep(game->time_to_die, game->for_timer);
		return ;
	}
	status_print(game, sing, TFORK);
	feeding_sycle(game, sing);
}

void	*philo_run(void *arg)
{
	t_pg	*game;
	t_th	*sing;

	sing = (t_th *)arg;
	game = sing->game_link;
	while (1)
		if (game->allphilo)
			break ;
	if (sing->uniqid % 2 == 0)
		u_my_sleep(game->time_to_eat - 1, game->for_timer);
	while (1)
	{
		if (game->death_status == -3)
			break ;
		else if (sing->count_meal == sing->game_link->pici)
			break ;
		eat_think_sleep(game, sing);
	}
	return (NULL);
}
