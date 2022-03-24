/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:31:49 by ttokesi           #+#    #+#             */
/*   Updated: 2022/03/22 11:47:38 by ttokesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_staff(t_th *sing)
{
	free(sing->game_link);
	free(sing);
	return (0);
}

static int	killer_the_ii(t_th	*sing, int time_to_die)
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

void	*the_killer(void *arg)
{
	t_th	*sing;
	int		time_to_die;

	sing = arg;
	time_to_die = sing->game_link->time_to_die;
	while (1)
	{
		if (killer_the_ii(sing, time_to_die))
		{
			return (NULL);
		}
		usleep(512);
	}
	return (NULL);
}
