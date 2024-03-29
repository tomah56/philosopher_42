/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_brain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:32:05 by ttokesi           #+#    #+#             */
/*   Updated: 2022/03/22 13:35:24 by ttokesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	load_values(t_th *sing, t_pg *game)
{
	int	j;

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

static int	kill_them_all(t_th *sing)
{
	int	j;

	j = 0;
	waitpid(0, NULL, 0);
	u_my_sleep(sing[0].game_link->time_to_die * 1.1, 200);
	while (j < sing->game_link->number_of_philosophers)
	{
		kill(sing[j].id, 2);
		j++;
	}
	free_staff(sing);
	exit(EXIT_SUCCESS);
	return (0);
}

int	load_game(t_pg *game)
{
	t_th	*sing;
	int		i;

	sing = malloc((game->number_of_philosophers) * sizeof(t_th));
	if (sing == NULL)
		return (0);
	load_values(sing, game);
	sem_unlink("/spoons");
	sem_unlink("/print");
	game->spoons = sem_open("/spoons", O_CREAT | O_EXCL, S_IRWXU,
			game->number_of_philosophers);
	game->lock = sem_open("/print", O_CREAT | O_EXCL, S_IRWXU, 1);
	i = 0;
	while (i < game->number_of_philosophers)
	{
		sing[i].id = fork();
		if (sing[i].id == 0)
		{
			philo_run(&sing[i]);
			return (0);
		}
		i++;
	}
	kill_them_all(sing);
	return (0);
}
