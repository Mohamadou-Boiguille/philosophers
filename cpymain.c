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

typedef struct s_input
{
	int				nb_philos;
	int				nb_of_meals;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				*fork_status;
	pthread_mutex_t	**fork_mutex;
	int				*philo_status;
	int				*last_meal;
	pthread_t		**philo_threads;
	struct timeval	action_time;
}					t_input;

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

void	ft_destroy_fork_mutex(t_input *set)
{
	int	i;

	i = 0;
	while (i < set->nb_philos)
		pthread_mutex_destroy(set->fork_mutex[i++]);
}

pthread_mutex_t	**ft_create_mutex(t_input *set)
{
	int				i;
	pthread_mutex_t	**mutex_as_fork;

	i = 0;
	mutex_as_fork = malloc(set->nb_philos * sizeof(pthread_mutex_t *));
	while (i < set->nb_philos)
	{
		mutex_as_fork[i] = malloc(sizeof(pthread_mutex_t));
		if (!mutex_as_fork[i])
		{
			ft_free_malloced_array((void **)mutex_as_fork, i);
			ft_free_malloced_array((void **)set->philo_threads, set->nb_philos);
			return (NULL);
		}
		pthread_mutex_init(mutex_as_fork[i], NULL);
		i++;
	}
	return (mutex_as_fork);
}

int	ft_create_threads(t_input *set)
{
	int	i;
	int	err_status;

	i = 0;
	while (i < set->nb_philos)
	{
		if (pthread_create(set->philo_threads[i], NULL, &func1, NULL) != 0)
		{
			ft_free_malloced_array((void **)set->fork_mutex, i);
			ft_free_malloced_array((void **)set->philo_threads, set->nb_philos);
			return (-1);
		}
		i++;
	}
	i = 0;
	while (i < set->nb_philos)
		pthread_join(*set->philo_threads[i++], NULL);
	return (0);
}

pthread_t	**ft_init_threads(t_input *set)
{
	int			i;
	pthread_t	**threads;

	i = 0;
	threads = malloc(set->nb_philos * sizeof(pthread_t *));
	while (i < set->nb_philos)
	{
		threads[i] = malloc(sizeof(pthread_t));
		if (!threads[i])
		{
			ft_free_malloced_array((void **)threads, i);
			return (NULL);
		}
		i++;
	}
	return (threads);
}

int	*init_first_meal(t_input *set)
{
	int	i;
	int	*last_meal;

	i = 0;
	last_meal = malloc(set->nb_philos * sizeof(int));
	if (!last_meal)
		return (NULL);
	gettimeofday(&set->action_time, NULL);
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
	input->eat_time = ft_atoi(args[3]);
	input->sleep_time = ft_atoi(args[4]);
	input->fork_status = calloc(input->nb_philos, sizeof(int));
	input->philo_status = calloc(input->nb_philos, sizeof(int));
	input->last_meal = init_first_meal(input);
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
    int     nb_of_deaths;

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
