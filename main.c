#define EAT "is eating"
#define FORK "has taken a fork"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define DIE "is died"

#include "libft/libft.h"
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_fork
{
	int				fork_status;
	pthread_mutex_t	*fork_mutex;
}					t_fork;

typedef struct s_philosopher
{
	int				philo_status;
	pthread_t		*philo_threads;
	int				*last_meal;
}					t_philo;

typedef struct s_input
{
	int				nb_philos;
	int				death_count;
	int				nb_of_meals;
	int				die_time;
	int				eat_duration;
	int				sleep_duration;
	int				*philo_status;
	int				first_meal;
	struct timeval	start_time;
	t_fork			*forks;
	t_philo			*philos;
}					t_input;

void	ft_init_forks(t_input *inputs)
{
	int	i;

	i = 0;
	inputs->forks = malloc(inputs->nb_philos * sizeof(t_fork));
	if (!inputs->forks)
		return ;
	while (i < inputs->nb_philos)
	{
		inputs->forks[i].fork_status = 1;
		pthread_mutex_init(inputs->forks[i].fork_mutex, NULL);
	}
}

void	ft_init_philos(t_input *inputs)
{
	int	i;

	i = 0;
	inputs->philos = malloc(inputs->nb_philos * sizeof(t_philo));
	if (!inputs->philos)
		return ;
	while (i < inputs->nb_philos)
	{
		inputs->philos[i].philo_status = 1;
		pthread_create(inputs->philos[i].philo_threads, NULL,
				&ft_philo_behavior, (void *)inputs);
	}
	i = 0;
	while (i < inputs->nb_philos)
		pthread_join(inputs->philos[i].philo_threads, NULL);
}

void	ft_print_log(int timestamp, int philosopher_nb, char *action)
{
	printf("%d %d %s\n", timestamp, philosopher_nb, action);
}

void	*func1(void *arg)
{
	write(1, "func1\n", 6);
	return (NULL);
}

void	ft_free_malloced_array(void **array, int index)
{
	while (index >= 0)
	{
		free(array[index]);
		if (index == 0)
			break ;
		index--;
	}
	free(array);
}

int	*init_first_meal(t_input *set)
{
	int	i;
	int	*last_meal;

	i = 0;
	last_meal = malloc(set->nb_philos * sizeof(int));
	if (!last_meal)
		return (NULL);
	while (i < set->nb_philos)
		last_meal[i++] = set->action_time.tv_usec;
	return (last_meal);
}

t_input	*ft_init_input(int nb_args, char **args)
{
	t_input	*input;

	input = malloc(sizeof(t_input));
	if (!input)
		return (NULL);
	input->nb_philos = ft_atoi(args[1]);
	input->die_time = ft_atoi(args[2]);
	input->eat_duration = ft_atoi(args[3]);
	input->sleep_duration = ft_atoi(args[4]);
	gettimeofday(&input->start_time, NULL);
	if (nb_args == 6)
		input->nb_of_meals = ft_atoi(args[5]);
	else
		input->nb_of_meals = -1;
	return (input);
}
//1 = eating
//2 = sleeping
//3 = died
//4 = thinking
int	ft_philo_behavior(t_input *set, int *nb_of_deaths, int philo_nb)
{
	if (set->philo_status[philo_nb] > 0)
		return (set->philo_status[philo_nb]);
	pthread_mutex_lock(set->fork_mutex[philo_nb]);
	pthread_mutex_lock(set->fork_mutex[(philo_nb + 1) % set->nb_philos]);
	gettimeofday(&set->action_time, NULL);
	if (set->last_meal[philo_nb] + set->eat_time >= set->action_time.tv_usec)
	{
		set->philo_status[philo_nb] = 3;
		return (set->philo_status[philo_nb]);
	}
	set->last_meal[philo_nb] = set->action_time.tv_usec;
	set->philo_status[philo_nb] = 1;
	ft_print_log(set->action_time.tv_usec, philo_nb, EAT);
	usleep(set->eat_time);
	pthread_mutex_unlock(set->fork_mutex[philo_nb]);
	pthread_mutex_unlock(set->fork_mutex[(philo_nb + 1) % set->nb_philos]);
	set->philo_status[philo_nb] = 2;
	usleep(set->sleep_time);
	set->philo_status[philo_nb] = 0;
	return (1);
}

int	main(int argc, char **argv)
{
	t_input	*input_set;
	int		nb_of_deaths;

	if (argc < 5)
		exit(EXIT_FAILURE);
	input_set = ft_init_input(argc, argv);
	if (!input_set)
		exit(EXIT_FAILURE);
	input_set->philo_threads = ft_init_threads(input_set);
	input_set->fork_mutex = ft_create_mutex(input_set);
	ft_destroy_fork_mutex(input_set);
	// ft_free_malloced_array(input_set->last_meal, input_set->nb_philos)
	return (0);
}
