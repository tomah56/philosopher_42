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
	int				time_to_die; // they die if they dont eat this long
	int				time_to_eat; // they hold the forks and eat this amount of time
	int				time_to_sleep; // they sleep this amunt of time 
	int				number_of_times_each_philosopher_must_eat;
	int				pici;
	int				stopcount;
	long			startime;
	// int				actual;
	int				death_status;
	int				for_timer;
	pthread_mutex_t	*forks;
	pthread_t	watch_dog;
	pthread_mutex_t	lock;
}	t_pg;

typedef struct s_singleton
{
	pthread_t	philo_thr;
	int			uniqid;
	long		time_now;
	long		was_eat;
	int			count_meal;
	// int			stop; // need this?
	t_pg		*game_link;
}	t_th;

long	ft_long_atoi(const char *str);
void	*philo_run(void *arg);
int		crossroad(char *args, int number, int time);

// new life

int	load_game(t_pg *game);

#endif
