/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:31:49 by ttokesi           #+#    #+#             */
/*   Updated: 2022/03/18 13:32:00 by ttokesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_staff(t_th *sing)
{
	int	i;

	i = 0;
	while (i < sing->game_link->number_of_philosophers)
	{
		pthread_mutex_destroy(&sing->game_link->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&sing->game_link->lock);
	free(sing->game_link->forks);
	usleep(1000);
	free(sing);
	return (0);
}
