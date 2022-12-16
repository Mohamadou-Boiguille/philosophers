#define EAT 1   //is eating
#define FORK 2  //has taken a fork
#define SLEEP 3 //is sleeping
#define THINK 4 //is thinking
#define DIED 5  //is died
#define USLEEP_T 1000

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
	int				death;
	unsigned long	die_time;
	unsigned long	eat_duration;
	unsigned long	sleep_duration;
	unsigned long	start_time;
}					t_input;

typedef struct s_thread
{
	t_input			*set;
	int				index;
	pthread_t		*thread;
	pthread_mutex_t	*forks;
	int				status;
	int				last_meal;
}					t_thread;

void	ft_print_log(int timestamp, int philosopher_nb, int action)
{
	if (action == EAT)
		printf("%d %d %s\n", timestamp, philosopher_nb, "eats");
	if (action == FORK)
		printf("%d %d %s\n", timestamp, philosopher_nb, "has taken a fork");
	if (action == 5)
		printf("%d %d %s\n", timestamp, philosopher_nb, "has release forks");
	if (action == SLEEP)
		printf("%d %d %s\n", timestamp, philosopher_nb, "sleeps");
	if (action == THINK)
		printf("%d %d %s\n", timestamp, philosopher_nb, "thinks");
}

void get_forks(t_thread *philo)
{
    int i;
    struct timeval curr_time;

    i = philo->index;
    if (philo->index % 2 == 0)
    {
        pthread_mutex_lock(&philo->forks[i]);
        ft_print_log(philo->last_meal, philo->index, EAT);
        pthread_mutex_lock(&philo->forks[(i + 1) % philo->set->nb_philos]);
        ft_print_log(philo->last_meal, philo->index, EAT);
    }
    else
    {
        pthread_mutex_lock(&philo->forks[(i + 1) % philo->set->nb_philos]);
        ft_print_log(philo->last_meal, philo->index, EAT);
        pthread_mutex_lock(&philo->forks[i]);
        ft_print_log(philo->last_meal, philo->index, EAT);
    }
    gettimeofday(&curr_time, NULL);
    philo->last_meal = curr_time.tv_usec;
    ft_print_log(philo->last_meal, philo->index, EAT);
    philo->status = SLEEP;
}

void release_forks(t_thread *philo)
{
    int i;
    struct timeval curr_time;

    i = philo->index;
    pthread_mutex_unlock(&philo->forks[(i + 1) % philo->set->nb_philos]);
    pthread_mutex_unlock(&philo->forks[i]);
    gettimeofday(&curr_time, NULL);
    ft_print_log(curr_time.tv_usec, philo->index, EAT);
}

void    sleeping(unsigned long sleep_time)
{
    while (sleep_time - USLEEP_T > 0)
    {
        usleep(USLEEP_T);
        sleep_time -= USLEEP_T;
    }
    usleep(sleep_time);
}

void ft_simulation(void *philo)
{
    t_thread *philosopher;

    philosopher = (t_thread *) philo;
    while (philosopher->set->death != 0)
    {
        philosopher->status = THINK;
        get_forks(philosopher);
        release_forks(philosopher);
        sleeping(philosopher->set->sleep_duration);
    }
}

pthread_mutex_t	*ft_init_forks(t_input *inputs)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(inputs->nb_philos * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	while (i < inputs->nb_philos)
		pthread_mutex_init(&forks[i++], NULL);
	return (forks);
}

t_thread	*ft_init_threads(t_input *inputs)
{
	int				i;
	t_thread		*threads;
	pthread_mutex_t	*forks;

	i = 0;
	forks = ft_init_forks(inputs);
	if (!forks)
		return (NULL);
	threads = malloc(inputs->nb_philos * sizeof(t_thread));
	if (!threads)
		return (NULL);
	while (i < inputs->nb_philos)
	{
		threads[i].set = inputs;
		threads[i].index = i;
		threads[i].status = THINK;
		threads[i].forks = forks;
		threads[i].last_meal = inputs->start_time;
		threads[i].thread = malloc(sizeof(pthread_t));
		pthread_create(threads[i].thread, NULL, (void *)ft_simulation,
				(void *)&threads[i]);
		i++;
	}
	i = 0;
	while (i < inputs->nb_philos)
		pthread_join(*(threads[i++].thread), NULL);
	return (threads);
}

t_input	*ft_init_input(int nb_args, char **args)
{
	t_input			*input;
	struct timeval	start;

	input = malloc(sizeof(t_input));
	if (!input)
		return (NULL);
	gettimeofday(&start, NULL);
	input->nb_of_meals = -1;
	input->nb_philos = ft_atoi(args[1]);
	input->die_time = ft_atoi(args[2]);
	input->eat_duration = ft_atoi(args[3]);
	input->sleep_duration = ft_atoi(args[4]);
	input->death = 0;
	if (nb_args == 6)
		input->nb_of_meals = ft_atoi(args[5]);
	input->start_time = start.tv_usec;
	return (input);
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
//1 = eating
//2 = sleeping
//3 = died
//4 = thinking

void	ft_destroy_fork_mutex(pthread_mutex_t *forks, int len)
{
	int	i;

	i = 0;
	while (i < len)
		pthread_mutex_destroy(&forks[i++]);
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
    ft_init_threads(input_set);
	ft_destroy_fork_mutex(NULL, 0);
	// ft_free_malloced_array(input_set->last_meal, input_set->nb_philos)
	return (0);
}
