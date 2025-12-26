/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 18:02:30 by rmamzer           #+#    #+#             */
/*   Updated: 2025/12/26 20:32:09 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"


void free_tablle(t_academy *table)
{
	if(table->philo)
		free(table->philo);
	if(table->fork)
		free(table->fork);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}


bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}



void write_error_msg(char *msg)
{
	write (STDERR_FILENO, msg, ft_strlen(msg));
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
	table->philo = NULL;
	table->fork = NULL;
	table->philos_total = philo_atoi(argv[1]);
	table->time_to_die = philo_atoi(argv[2]);
	table->time_to_eat = philo_atoi(argv[3]);
	table->time_to_sleep = philo_atoi(argv[4]);
	if (argc ==  6)
		table->num_of_meals = philo_atoi(argv[5]);
	else
		table->num_of_meals = 0;
	table->philo == malloc(sizeof(t_philo) * table->philos_total);
		if(!table->philo)
			return(write_error_msg(ERROR_MEM),FAILURE);
	table->fork == malloc(sizeof(t_philo) * table->philos_total);
		if(!table->fork)
			return(write_error_msg(ERROR_MEM),FAILURE);
	return(SUCCESS);
}


bool init_mutexes(t_academy *table)
{
	int	i;

	i = 0;
	while (i < table->philos_total)
	{

	}


	return (SUCCESS);
}



bool init_data( int argc, char **argv, t_academy *table)
{
	if (init_table(argc, argv, table)== FAILURE)
		return (free_table(table), FAILURE);
	if (init_mutexes(table)== FAILURE)
		return(free_table(table), FAILURE);
	return (SUCCESS);

}


int	main(int argc, char **argv)
{
	t_academy table;

	if (check_input(argc, argv) == FAILURE)
		return(FAILURE);
	if (init_data(argc, argv, &table) == FAILURE)
		return(FAILURE);
	return (SUCCESS);
}