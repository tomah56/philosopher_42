/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttokesi <ttokesi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:32:23 by ttokesi           #+#    #+#             */
/*   Updated: 2022/03/24 16:58:36 by ttokesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>
# include <stdlib.h>

enum e_nums
{
	FAIL = -1,
	DIE,
	SLEEP,
	EAT,
	THINK,
	TFORK
};

typedef struct s_philo_game
{
	int				allphilo;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				pici;
	int				stopcount;
	long			startime;
	int				death_status;
	int				for_timer;
	pthread_mutex_t	*forks;
	pthread_t		watch_dog;
	pthread_mutex_t	lock;
}	t_pg;

typedef struct s_singleton
{
	pthread_t	philo_thr;
	int			uniqid;
	long		time_now;
	long		was_eat;
	int			count_meal;
	t_pg		*game_link;
}	t_th;

long	ft_long_atoi(const char *str);
void	*philo_run(void *arg);
int		load_game(t_pg *game);
int		free_staff(t_th *sing);
void	u_my_sleep(long time_to, int for_time);

#endif
