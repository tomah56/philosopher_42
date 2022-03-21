/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:32:34 by ttokesi           #+#    #+#             */
/*   Updated: 2022/03/21 15:55:50 by ttokesi          ###   ########.fr       */
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

static void	dead_my_sleep(long time_to, int for_time, t_pg *game, t_th *sing)
{
	struct timeval	c_time;
	long			start;
	long			i;
	long		time_calculated;
	long		time_of_death;

	i = 0;
	gettimeofday(&c_time, NULL);
	start = (c_time.tv_usec / 1000) + (c_time.tv_sec * 1000);
	// printf(" start - gamestart: %ld time_to: %ld was_eat: %ld  time_to_die: %d\n", start - game->startime, time_to, sing->was_eat, game->time_to_die);
	time_calculated = start - game->startime + time_to;
	time_of_death = sing->was_eat + game->time_to_die;
	// printf("time_calcualted; %ld time of death: %ld\n", time_calculated, time_of_death);
		if (time_calculated >= time_of_death )
		{
			// usleep(time_calculated - time_of_death);
				// while (i < start + time_calculated - time_of_death - 1)
				// {
				// 	usleep(for_time);
				// 	gettimeofday(&c_time, NULL);
				// 	i = (c_time.tv_usec / 1000) + (c_time.tv_sec * 1000);
				// }
			sem_wait(game->lock);
			sing[i].game_link->death_status = -3;
			// i = (c_time.tv_usec / 1000) + (c_time.tv_sec * 1000);
			printf("%ld %d died\n", time_of_death, sing->uniqid + 1);
			exit(EXIT_SUCCESS);
			return ;
			// sem_post(game->lock);
		}
	while (i < start + time_to)
	{
		usleep(for_time);
		gettimeofday(&c_time, NULL);
		i = (c_time.tv_usec / 1000) + (c_time.tv_sec * 1000);
		// if (i - game->startime - sing->was_eat >= game->time_to_die )
		// {
		// 	sem_wait(game->lock);
		// 	sing[i].game_link->death_status = -3;
		// 	i = (c_time.tv_usec / 1000) + (c_time.tv_sec * 1000);
		// 	printf("%ld %d died\n", i - game->startime, sing->uniqid + 1);
		// 	return ;
		// 	// sem_post(game->lock);
		// }
	}
}

static void	feeding_sycle(t_pg *game, t_th *sing)
{
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

static void	eat_think_sleep(t_pg *game, t_th *sing)
{
	sem_wait(game->spoons);
	status_print(game, sing, TFORK);
	sem_wait(game->spoons);
	status_print(game, sing, TFORK);
	feeding_sycle(game, sing);
}

static int	killer_the_ii(t_th	*sing, int stop, int time_to_die, int i)
{
	struct timeval	c_time;
	long			now;

	gettimeofday(&c_time, NULL);
	now = (c_time.tv_usec / 1000) + (c_time.tv_sec * 1000)
		- sing->game_link->startime;
	if (now - sing->was_eat >= time_to_die)
	{
		sem_wait(sing->game_link->lock);
		sing->game_link->death_status = -3;
		printf("%ld %d died\n", now, sing->uniqid + 1);
		exit(EXIT_SUCCESS);
		return (1);
	}
	return (0);
}

static void	*the_killer(void *arg)
{
	t_th	*sing;
	int		stop;
	int		time_to_die;

	sing = arg;
	stop = sing->game_link->number_of_philosophers;
	time_to_die = sing->game_link->time_to_die;
	while (1)
	{
		if (killer_the_ii(sing, stop, time_to_die, 0))
		{
			return (NULL);
		}
		usleep(512);
	}
	return (NULL);
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
		{
			return (0);
		}
		else if (sing->count_meal == sing->game_link->pici)
			return (0);
		else
			eat_think_sleep(game, sing);
	}
	ret = pthread_join(sing->watch_dog, NULL);
	// if (ret !ma(free_staff(sing));
	return (0);
}
