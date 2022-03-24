/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:32:34 by ttokesi           #+#    #+#             */
/*   Updated: 2022/03/24 16:55:48 by ttokesi          ###   ########.fr       */
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
	sem_wait(game->lock);
	gettimeofday(&c_time, NULL);
	sing->time_now = ((c_time.tv_usec / 1000) + (c_time.tv_sec * 1000))
		- game->startime;
	if (game->death_status == 0)
		printf("%ld %d %s\n", sing->time_now, sing->uniqid + 1, temp);
	sem_post(game->lock);
}

void	u_my_sleep(long time_to, int for_time)
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

static void	eat_think_sleep(t_pg *game, t_th *sing)
{
	sem_wait(game->spoons);
	status_print(game, sing, TFORK);
	sem_wait(game->spoons);
	status_print(game, sing, TFORK);
	status_print(game, sing, EAT);
	sing->was_eat = sing->time_now;
	sing->count_meal++;
	u_my_sleep(game->time_to_eat, game->for_timer);
	sem_post(game->spoons);
	sem_post(game->spoons);
	if (sing->count_meal == sing->game_link->pici)
		return ;
	status_print(game, sing, SLEEP);
	u_my_sleep(game->time_to_sleep, game->for_timer);
	status_print(game, sing, THINK);
}

int	philo_run(t_th	*sing)
{
	t_pg	*game;
	int		ret;

	game = sing->game_link;
		ret = pthread_create(&sing->watch_dog, NULL, &the_killer, sing);
	if (ret != 0)
		return (free_staff(sing));
	while (1)
	{
		if (game->death_status == -3)
			exit(EXIT_SUCCESS);
		else if (sing->count_meal == sing->game_link->pici)
			exit(EXIT_SUCCESS);
		else
			eat_think_sleep(game, sing);
	}
	ret = pthread_join(sing->watch_dog, NULL);
	if (ret != 0)
		return (free_staff(sing));
	return (0);
}
