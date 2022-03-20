/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:32:34 by ttokesi           #+#    #+#             */
/*   Updated: 2022/03/20 02:40:38 by ttokesi          ###   ########.fr       */
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
	
	// u_my_sleep(game->time_to_eat, game->for_timer);
	dead_my_sleep(game->time_to_eat, game->for_timer, game, sing);
	sem_post(game->spoons);
	sem_post(game->spoons);
	// if (sing->uniqid != game->number_of_philosophers - 1)
	// 	pthread_mutex_unlock(&game->forks[sing->uniqid + 1]);
	// else
	// 	pthread_mutex_unlock(&game->forks[0]);
	// pthread_mutex_unlock(&game->forks[sing->uniqid]);
	if (sing->count_meal == sing->game_link->pici)
		return ;
	status_print(game, sing, SLEEP);
	// u_my_sleep(game->time_to_sleep, game->for_timer);
	dead_my_sleep(game->time_to_sleep, game->for_timer, game, sing);
	status_print(game, sing, THINK);
}

static void	eat_think_sleep(t_pg *game, t_th *sing)
{
	// if (sing->uniqid != game->number_of_philosophers - 1)
	// 	pthread_mutex_lock(&game->forks[sing->uniqid + 1]);
	// else if (game->number_of_philosophers != 1)
	// {
	// 	pthread_mutex_lock(&game->forks[0]);
	// }
	// if (game->number_of_philosophers != 1)
	// 	pthread_mutex_lock(&game->forks[sing->uniqid]);
	// else
	// {
	// 	u_my_sleep(game->time_to_die, game->for_timer);
	// 	return ;
	// }
	// if (sing->count_meal == sing->game_link->pici)
	// 	return ;
	sem_wait(game->spoons);
	status_print(game, sing, TFORK);
	sem_wait(game->spoons);
	status_print(game, sing, TFORK);
	feeding_sycle(game, sing);
}

int	philo_run(t_th	*sing)
{
	t_pg	*game;

	game = sing->game_link;
	// write(1, "HELLO\n", 6);
	// while (1)
	// {
	// 	if (game->allphilo)
	// 		break ;
	// }
	// write(1, "HE__O\n", 6);
	// if (sing->uniqid % 2 == 0)
	// 	u_my_sleep(game->time_to_eat - 1, game->for_timer);
	// sleep(60);
	while (1)
	{
		// printf("---%d ------ %d--------- pid: %d  id:%d\n", sing->count_meal, sing->uniqid, getpid(), sing->id);
		if (game->death_status == -3)
			return (0);
		else if (sing->count_meal == sing->game_link->pici)
			return (0);
		else
			eat_think_sleep(game, sing);
	}
	return (0);
}
