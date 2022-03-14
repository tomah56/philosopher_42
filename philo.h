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
	DIE,
	SLEEP,
	EAT,
	THINK
};

typedef struct s_philo_game
{
	int				*allphilo;
	int				*forks;
	int				*lastmeal;
	int				stopcount;
	long			startime;
	pthread_t		philo_thr;
	pthread_mutex_t	lock;
}	t_pg;

typedef struct s_singleton
{
	t_pg			*game_link;
	pthread_mutex_t	forks;
	pthread_mutex_t	statuses;
	long			startime;
	int				actual;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				uniqid;
}	t_th;

long	ft_long_atoi(const char *str);
void	*philo_run(void *arg);
int		crossroad(char *args, int number);

#endif
