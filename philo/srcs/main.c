/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 18:02:30 by rmamzer           #+#    #+#             */
/*   Updated: 2025/12/27 18:29:49 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"


size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void write_error_msg(char *msg)
{
	write (STDERR_FILENO, msg, ft_strlen(msg));
}

bool	mutex_action(pthread_mutex_t *mutex, t_action action)
{
	if (action == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			return (write_error_msg(ERROR_MTX_INIT), FAILURE);
	}
	else if (action == LOCK)
		pthread_mutex_lock(mutex);
	else if (action == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (action == DESTROY)
		pthread_mutex_destroy(mutex);
	return (SUCCESS);
}

void	destroy_forks(t_academy *table, int forks_total)
{
	int i;

	i = 0;
	while(i < forks_total)
	{
		mutex_action(&table->forks[i], DESTROY);
		i++;
	}
}

void free_table(t_academy *table)
{
	if(table->philos)
		free(table->philos);
	if(table->forks)
		free(table->forks);
}

\

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}


bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}




bool check_arg_num(int argc)
{
	if (argc !=5 && argc !=6)
		return(FAILURE);
	return (SUCCESS);

}


bool	ft_check_overflow_and_zero(char *nptr)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	while (ft_isspace(nptr[i]))
		i++;
	while (ft_isdigit(nptr[i]))
	{
		num = num * 10 + (nptr[i] - '0');
		if (num >INT_MAX)
			return(write_error_msg(ERROR_INTOVRF), FAILURE);
		i++;
	}
	if (num == 0)
		return(write_error_msg(ERROR_ARGZERO), FAILURE);
	return (SUCCESS);
}


bool check_input(int argc, char **argv)
{
	int i;
	int j;

	if (check_arg_num(argc)== FAILURE)
		return (write_error_msg(ERROR_ARGSN),FAILURE);
	i = 0;
	while(argv[++i])
	{
		j=0;
		while (argv[i][j] && ft_isspace(argv[i][j]))
			j++;
		if (argv[i][j] == '\0')
			return(write_error_msg(ERROR_ARGEMPTY), FAILURE);
		while (argv[i][j] && ft_isdigit(argv[i][j]))
			j++;
		if (argv[i][j] != '\0')
			return (write_error_msg(ERROR_ARG), FAILURE);
		if (ft_check_overflow_and_zero(argv[i]))
			return (FAILURE);
	}
	return (SUCCESS);
}


int philo_atoi(const char *nstr)
{
	int	num;
	int		i;

	i = 0;
	num = 0;
	while(ft_isspace(nstr[i]))
		i++;
	while(ft_isdigit(nstr[i]))
	{
		num = num * 10 + (nstr[i] - '0');
		i++;
	}
	return(num);
}



bool	init_table(int argc, char **argv, t_academy *table)
{
	table->philos = NULL;
	table->forks = NULL;
	table->philos_total = philo_atoi(argv[1]);
	table->time_to_die = philo_atoi(argv[2]);
	table->time_to_eat = philo_atoi(argv[3]);
	table->time_to_sleep = philo_atoi(argv[4]);
	if (argc ==  6)
		table->num_of_meals = philo_atoi(argv[5]);
	else
		table->num_of_meals = 0;
	table->time_start = get_time();
	table->philos = malloc(sizeof(t_philo) * table->philos_total);
		if(!table->philos)
			return(write_error_msg(ERROR_MEM),FAILURE);
	table->forks = malloc(sizeof(t_philo) * table->philos_total);
		if(!table->forks)
			return(write_error_msg(ERROR_MEM),FAILURE);
	return(SUCCESS);
}


bool init_mutexes(t_academy *table)
{
	int	i;

	i = 0;
	while (i < table->philos_total)
	{
		if (mutex_action(&table->forks[i], INIT)== FAILURE)
			return(destroy_forks(table, table->philos_total),FAILURE);
		i++;
	}
	if (mutex_action(&table->mtx_msg, INIT)== FAILURE)
		return(destroy_forks(table, table->philos_total),FAILURE);
	return (SUCCESS);
}


void	give_forks(t_academy *table, t_philo *philo, int i)
{
	if (philo->id % 2)
	{
		philo->first_fork = &table->forks[(i+1) % table->philos_total];
		philo->second_fork = &table->forks[i];
	}
	else
	{
		philo->first_fork = &table->forks[i];
		philo->second_fork = &table->forks[(i+1) % table->philos_total];
	}
}




void	init_philosophers(t_academy *table)
{
	int i;
	t_philo *philo;

	i = 0;
	while (i < table->philos_total)
	{
		philo = table->philos;
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->last_meal_time = table->time_start;
		//philo->table = table;
		give_forks(table, philo, i);
		i++;
	}

}


bool init_data( int argc, char **argv, t_academy *table)
{
	if (init_table(argc, argv, table)== FAILURE)
		return (free_table(table), FAILURE);
	if (init_mutexes(table)== FAILURE)
		return(free_table(table), FAILURE);
	init_philosophers(table);
	return (SUCCESS);
}




bool	thread_action(pthread_t thread, void *data, void *(*function)(void *), t_action action )
{
	if (action == CREATE)
	{
		pthread_create(thread, NULL, function, data);
	}
}

void	*life(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	
}



bool	create_threads(t_academy *table)
{
	int i;

	i = 0;
	while (i < table->philos_total)
	{
		if(thread_action(&table->philos[i].thread, &table->philos[i], life, CREATE))

		i++;
	}
	return (SUCCESS);
}

bool open_academy(t_academy *table)
{
	create_threads(table);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_academy table;

	if (check_input(argc, argv) == FAILURE)
		return(FAILURE);
	if (init_data(argc, argv, &table) == FAILURE)
		return(FAILURE);
	if (open_academy(&table)== FAILURE)
		return (FAILURE);
	//clean before exit
	return (SUCCESS);
}