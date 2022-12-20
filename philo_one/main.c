dprintf(2, "current_time = %lu | target = %lu \n", , target);
	while (current_time < target)
	{
		usleep(USLEEP_T);
		current_time = get_timestamp(philo->set->start_time);
		// if (philo->index == 0)
		//     dprintf(2, "current_time = %lu | target = %lu | action = %d\n",
		// current_time, target, action);
	}
}

int	fork_access(pthread_mutex_t *fork, int *status, int get_or_put)
{
	int	had_access;

	had_access = 0;
	pthread_mutex_lock(fork);
	if (*status == AVAILABLE && get_or_put == GET)
	{
		had_access = 1;
		*status = USED;
	}
	else if (*status == USED && get_or_put == PUT)
	{
		had_access = 1;
		*status = AVAILABLE;
	}
	pthread_mutex_unlock(fork);
	return (had_access);
}

int	is_alive(t_thread *philo)
{
	unsigned	current_time;

	current_time = get_timestamp(philo->set->start_time);
	if (philo->last_meal + philo->set->die_time < current_time)
	{
		pthread_mutex_lock(&philo->set->death_mutex);
		philo->set->end_simulation += 1;
		if (philo->set->end_simulation == 1)
		{
            ft_print_log(current_time, philo->index, DIED);
			return current_time;
		}
		pthread_mutex_unlock(&philo->set->death_mutex);
	}
	else
		current_time = 0;
	return (current_time);
}

int	get_forks(t_thread *philo, int f_one, int f_two)
{
	unsigned long	tstamp;

	while (!fork_access(&philo->f_mutex[f_one], &philo->f_status[f_one], GET))
	{
		tstamp = is_alive(philo);
		if (tstamp)
			return (0);
	}
	tstamp = get_timestamp(philo->set->start_time);
	ft_print_log(tstamp, philo->index, FORK);
	while (!fork_access(&philo->f_mutex[f_two], &philo->f_status[f_two], GET))
	{
		tstamp = is_alive(philo);
		if (tstamp)
			ft_print_log(tstamp, philo->index, DIED);
			return (0);
	}
	tstamp = get_timestamp(philo->set->start_time);
	ft_print_log(tstamp, philo->index, FORK);
	return (1);
}

int	try_to_get_forks(t_thread *philo)
{
	int	left;
	int	right;

	left = philo->index;
	right = (philo->index + 1) % philo->set->nb_philos;
	if (philo->index % 2)
		return (get_forks(philo, right, left));
	else
		return (get_forks(philo, left, right));
}

void	release_forks(t_thread *philo)
{
	int			left;
	int			right;
	unsigned	tstamp;

	left = philo->index;
	right = (philo->index + 1) % philo->set->nb_philos;
	fork_access(&philo->f_mutex[left], &philo->f_status[left], PUT);
	fork_access(&philo->f_mutex[right], &philo->f_status[right], PUT);
	if (philo->set->end_simulation)
		return ;
	//no need to print log - debug purpose only
	tstamp = get_timestamp(philo->set->start_time);
	ft_print_log(tstamp, philo->index, UNFORK);
}

void	is_eating(t_thread *philo)
{
	unsigned long	tstamp;

	tstamp = get_timestamp(philo->set->start_time);
	philo->last_meal = tstamp;
	if (philo->set->end_simulation)
		return ;
	ft_print_log(tstamp, philo->index, EAT);
	freeze_thread(philo, EAT, philo->set->eat_duration, tstamp);
}

void	is_sleeping(t_thread *philo)
{
	unsigned long	tstamp;

	tstamp = get_timestamp(philo->set->start_time);
	if (philo->set->end_simulation)
		return ;
	ft_print_log(tstamp, philo->index, SLEEP);
	freeze_thread(philo, SLEEP, philo->set->sleep_duration, tstamp);
}

void	is_thinking(t_thread *philo)
{
	unsigned long	tstamp;

	tstamp = get_timestamp(philo->set->start_time);
	ft_print_log(tstamp, philo->index, THINK);
    usleep(100);
}

void	*ft_simulation(void *philosopher)
{
	t_thread	*philo;
	long		nb_of_meals;

	philo = (t_thread *)philosopher;
	while (philo->set->end_simulation == 0
		&& philo->set->every_meals_taken != philo->set->nb_philos)
	{
		if (philo->set->end_simulation)
			break ;
		if (nb_of_meals == philo->set->complete_nb_of_meals)
			philo->set->every_meals_taken += 1;
		if (!try_to_get_forks(philo))
			return (NULL);
		is_eating(philo);
		nb_of_meals++;
		release_forks(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}

pthread_mutex_t	*ft_init_forks(t_input *inputs)
{
	int				i;
	pthread_mutex_t	*f_mutex;

	//ft_calloc
	f_mutex = calloc(inputs->nb_philos, sizeof(pthread_mutex_t));
	if (!f_mutex)
	{
		free(inputs);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < inputs->nb_philos)
	{
		pthread_mutex_init(&f_mutex[i], NULL);
		//dprintf(2, "\n");
		i++;
	}
	return (f_mutex);
}

void	init_commons(t_input *inputs, t_thread *threads, int i, int start)
{
	threads[i].set = inputs;
	threads[i].index = i;
	threads[i].status = THINK;
	threads[i].last_meal = start;
}

void	join_threads(t_thread *threads, int nb_of_philos)
{
	int	i;

	i = 0;
	while (i < nb_of_philos)
	{
		pthread_join(*(threads[i].thread), NULL);
		i++;
	}
}

t_thread	*ft_init_threads(t_input *inputs)
{
	int				i;
	t_thread		*threads;
	pthread_mutex_t	*f_mutex;
	int				*f_status;
	int				start;

	i = 0;
	gettimeofday(&inputs->start_time, NULL);
	start = get_timestamp(inputs->start_time);
	f_mutex = ft_init_forks(inputs);
	f_status = calloc(inputs->nb_philos, sizeof(int));
	threads = malloc(inputs->nb_philos * sizeof(t_thread));
	pthread_mutex_init(&inputs->death_mutex, NULL);
	if (!threads || !f_status)
		return (NULL);
	while (i < inputs->nb_philos)
	{
		init_commons(inputs, threads, i, start);
		threads[i].f_mutex = f_mutex;
		threads[i].f_status = f_status;
		threads[i].thread = malloc(sizeof(pthread_t));
		pthread_create(threads[i].thread, NULL, &ft_simulation,
				(void *)&threads[i]);
        usleep(1000);
		i++;
	}
	join_threads(threads, inputs->nb_philos);
	return (threads);
}

t_input	*ft_init_input(int nb_args, char **args)
{
	t_input	*input;

	input = malloc(sizeof(t_input));
	if (!input)
		return (NULL);
	gettimeofday(&input->start_time, NULL);
	//get ft_atoi
	input->complete_nb_of_meals = -1;
	input->nb_philos = atoi(args[1]);
	input->die_time = atoi(args[2]);
	input->eat_duration = atoi(args[3]);
	input->sleep_duration = atoi(args[4]);
	input->end_simulation = 0;
	input->every_meals_taken = 0;
	if (nb_args == 6)
		input->complete_nb_of_meals = atoi(args[5]);
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

void	ft_destroy_all_mutexes(pthread_mutex_t *f_mutex, int len)
{
	int	i;

	i = 0;
	while (i < len)
		pthread_mutex_destroy(&f_mutex[i++]);
}

void	ft_free_all(t_thread *threads)
{
	int	i;
	int	nb_philos;

	i = 0;
	nb_philos = threads->set->nb_philos;
	while (i < nb_philos)
		free(threads[i++].thread);
	free(threads->f_status);
	free(threads->f_mutex);
	free(threads->set);
	free(threads);
}

int	main(int argc, char **argv)
{
	t_input		*input_set;
	t_thread	*threads;

	if (argc < 5 || argc > 6)
		exit(EXIT_FAILURE);
	input_set = ft_init_input(argc, argv);
	if (!input_set)
		exit(EXIT_FAILURE);
	threads = ft_init_threads(input_set);
	usleep(2000);
	ft_destroy_all_mutexes(threads->f_mutex, 0);
	ft_free_all(threads);
	// ft_free_malloced_array(input_set->last_meal, input_set->nb_philos)
	return (0);
}
